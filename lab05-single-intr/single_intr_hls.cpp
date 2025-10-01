#include "single_intr_hls.h"

void single_intr_hls(
    bool reset,
    bool interrupt,
    ap_uint<8> normal_in,
    ap_uint<8> intr_in,
    ap_uint<8> &out_data,
    ap_uint<2> &status
) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=reset
#pragma HLS INTERFACE ap_none port=interrupt
#pragma HLS INTERFACE ap_none port=normal_in
#pragma HLS INTERFACE ap_none port=intr_in
#pragma HLS INTERFACE ap_none port=out_data
#pragma HLS INTERFACE ap_none port=status

    static ap_uint<8> data_reg = 0;
    static ap_uint<2> state = 0; // 0=IDLE, 1=NORMAL, 2=ISR

    if (reset) {
        data_reg = 0;
        state = 0;
    } else {
        if (interrupt) {
            data_reg = intr_in;
            state = 2;
        } else {
            data_reg = normal_in;
            state = 1;
        }
    }

    out_data = data_reg;
    status = state;
}
