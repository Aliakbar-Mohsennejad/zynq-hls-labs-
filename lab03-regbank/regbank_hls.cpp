#include "regbank_hls.h"

void regbank_hls(ap_uint<8> addr,
                 ap_uint<8> in_data,
                 bool write,
                 bool read,
                 bool enable,
                 ap_uint<8> &out_data) {
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS INTERFACE ap_none port=addr
    #pragma HLS INTERFACE ap_none port=in_data
    #pragma HLS INTERFACE ap_none port=write
    #pragma HLS INTERFACE ap_none port=read
    #pragma HLS INTERFACE ap_none port=enable
    #pragma HLS INTERFACE ap_none port=out_data

    // 256 x 8-bit register bank (RAM)
    static ap_uint<8> mem[256];
    #pragma HLS RESOURCE variable=mem core=RAM_1P

    // default
    out_data = 0;

    if (enable) {
        if (write) {
            mem[addr] = in_data;
        }
        if (read) {
            out_data = mem[addr];
        }
    }
}
