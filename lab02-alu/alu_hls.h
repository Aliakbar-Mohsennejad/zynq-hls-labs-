#ifndef ALU_HLS_H
#define ALU_HLS_H

#include <ap_int.h>

// op: 0 ADD, 1 SUB, 2 AND, 3 OR, 4 XOR, 5 NOT A, 6 INC A
// Flags:
// C: carry for ADD/INC; for SUB -> C = !borrow
// Z: zero, N: negative (MSB), V: signed overflow
void alu_hls_ex(ap_uint<8> A, ap_uint<8> B, ap_uint<3> op,
                ap_uint<8> &R, bool &C, bool &Z, bool &N, bool &V);

#endif
