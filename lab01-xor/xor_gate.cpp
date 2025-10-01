#include "xor_gate.h"

void xor_gate(bool a, bool b, bool &out) {
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS INTERFACE ap_none port=a
    #pragma HLS INTERFACE ap_none port=b
    #pragma HLS INTERFACE ap_none port=out

    out = a ^ b;
}
