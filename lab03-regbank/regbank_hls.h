#ifndef REGBANK_HLS_H
#define REGBANK_HLS_H

#include <ap_int.h>

// Simple 256x8 RAM with enable/read/write control.
// addr: 8-bit address
// in_data: 8-bit data to write
// write/read/enable: control signals (true/false)
// out_data: 8-bit read data (valid when read=1 and enable=1)
void regbank_hls(ap_uint<8> addr,
                 ap_uint<8> in_data,
                 bool write,
                 bool read,
                 bool enable,
                 ap_uint<8> &out_data);

#endif
