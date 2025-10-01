#include "multi_intr_hls.h"

static ap_uint<16> lfsr_next(ap_uint<16> s) {
    // x^16 + x^14 + x^13 + x^11 + 1 (maximal-length)
    bool b = s[0] ^ s[2] ^ s[3] ^ s[5];
    return (ap_uint<16>)((s >> 1) | ((ap_uint<16>)b << 15));
}

void multi_intr_hls(bool reset,
                    ap_uint<2> &irq,
                    ap_uint<2> &cpu_state,
                    bool &ig1, bool &ig2, bool &ig3) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=reset
#pragma HLS INTERFACE ap_none port=irq
#pragma HLS INTERFACE ap_none port=cpu_state
#pragma HLS INTERFACE ap_none port=ig1
#pragma HLS INTERFACE ap_none port=ig2
#pragma HLS INTERFACE ap_none port=ig3

    // System state (persistent across ticks)
    static ap_uint<16> l1 = 0xACE1, l2 = 0xBEEF, l3 = 0xC0DE;
    static ap_uint<3>  t1 = 0, t2 = 0, t3 = 0;      // 0..4 tick within 50ns cycle
    static bool        on1 = false, on2 = false, on3 = false; // active this 50ns cycle?
    static bool        s1 = false, s2 = false, s3 = false;    // current IG outputs
    static ap_uint<2>  cpu = 0;                      // 0 normal, 1..3 ISR
    static ap_int<3>   isr_ticks = 0;               // remaining ticks in ISR (3 ticks = 30ns)
    static ap_uint<2>  current_irq = 0;

    if (reset) {
        l1 = 0xACE1; l2 = 0xBEEF; l3 = 0xC0DE;
        t1 = t2 = t3 = 0;
        on1 = on2 = on3 = false;
        s1 = s2 = s3 = false;
        cpu = 0; isr_ticks = 0; current_irq = 0;
        irq = 0; cpu_state = 0; ig1 = ig2 = ig3 = false;
        return;
    }

    // --- IG timing model: 50ns cycle -> 5 ticks of 10ns. If active, ON for 2 ticks then OFF for 3.
    // Decide (50% chance) at start of each 50ns cycle.
    if (t1 == 0) { on1 = (l1 & 1); l1 = lfsr_next(l1); }
    if (t2 == 0) { on2 = (l2 & 1); l2 = lfsr_next(l2); }
    if (t3 == 0) { on3 = (l3 & 1); l3 = lfsr_next(l3); }

    s1 = on1 && (t1 < 2);
    s2 = on2 && (t2 < 2);
    s3 = on3 && (t3 < 2);

    t1 = (t1 == 4) ? (ap_uint<3>)0 : (ap_uint<3>)(t1 + 1);
    t2 = (t2 == 4) ? (ap_uint<3>)0 : (ap_uint<3>)(t2 + 1);
    t3 = (t3 == 4) ? (ap_uint<3>)0 : (ap_uint<3>)(t3 + 1);

    // --- Interrupt Controller (priority: IG1 > IG2 > IG3)
    ap_uint<2> prio_irq = 0;
    if (s1)      prio_irq = 1;
    else if (s2) prio_irq = 2;
    else if (s3) prio_irq = 3;

    // --- CPU: 10ns "clock"; serve ISR for 30ns (3 ticks) when a new IRQ appears
    if (isr_ticks > 0) {
        isr_ticks = (ap_int<3>)(isr_ticks - 1);
        if (isr_ticks == 0) {
            cpu = 0;
            current_irq = 0;
        }
    } else {
        if (prio_irq != 0) {
            cpu = prio_irq;
            current_irq = prio_irq;
            isr_ticks = 3; // 30ns service time
        } else {
            cpu = 0;
        }
    }

    // Drive outputs
    irq = prio_irq;
    cpu_state = cpu;
    ig1 = s1; ig2 = s2; ig3 = s3;
}
