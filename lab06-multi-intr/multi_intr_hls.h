#ifndef MULTI_INTR_HLS_H
#define MULTI_INTR_HLS_H

#include <ap_int.h>

// Top function advances the system by one 10ns tick per call.
// Outputs report current IRQ code and CPU state.
// irq: 0=none, 1=IG1, 2=IG2, 3=IG3
// cpu_state: 0=normal, 1=ISR(IG1), 2=ISR(IG2), 3=ISR(IG3)
// ig1/ig2/ig3 are optional observability pins (interrupt lines)
void multi_intr_hls(bool reset,
                    ap_uint<2> &irq,
                    ap_uint<2> &cpu_state,
                    bool &ig1, bool &ig2, bool &ig3);

#endif
