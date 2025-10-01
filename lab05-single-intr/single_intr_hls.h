#ifndef SINGLE_INTR_HLS_H
#define SINGLE_INTR_HLS_H

#include <ap_int.h>

void single_intr_hls(
    bool reset,
    bool interrupt,
    ap_uint<8> normal_in,
    ap_uint<8> intr_in,
    ap_uint<8> &out_data,
    ap_uint<2> &status
);

#endif
