#include "alu_hls.h"

void alu_hls_ex(ap_uint<8> A, ap_uint<8> B, ap_uint<3> op,
                ap_uint<8> &R, bool &C, bool &Z, bool &N, bool &V) {
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS INTERFACE ap_none port=A
    #pragma HLS INTERFACE ap_none port=B
    #pragma HLS INTERFACE ap_none port=op
    #pragma HLS INTERFACE ap_none port=R
    #pragma HLS INTERFACE ap_none port=C
    #pragma HLS INTERFACE ap_none port=Z
    #pragma HLS INTERFACE ap_none port=N
    #pragma HLS INTERFACE ap_none port=V

    // defaults
    R = 0; C = 0; Z = 0; N = 0; V = 0;

    switch (op) {
    case 0: { // ADD
        ap_uint<9> sum = (ap_uint<9>)A + (ap_uint<9>)B;
        R = (ap_uint<8>)sum;
        C = sum[8]; // carry-out (unsigned)
        bool SA = A[7], SB = B[7], SR = R[7];
        V = (SA == SB) && (SR != SA); // signed overflow (ADD)
    } break;

    case 1: { // SUB  -> C = !borrow
        ap_uint<9> diff = (ap_uint<9>)A - (ap_uint<9>)B;
        R = (ap_uint<8>)diff;
        bool borrow = (A < B);
        C = !borrow;
        bool SA = A[7], SB = B[7], SR = R[7];
        V = (SA != SB) && (SR != SA); // signed overflow (SUB)
    } break;

    case 2: R = A & B; break;  // AND
    case 3: R = A | B; break;  // OR
    case 4: R = A ^ B; break;  // XOR
    case 5: R = ~A;    break;  // NOT A

    case 6: { // INC A
        ap_uint<9> inc = (ap_uint<9>)A + 1;
        R = (ap_uint<8>)inc;
        C = inc[8]; // carry-out
        bool SA = A[7], SB = 0, SR = R[7];
        V = (SA == SB) && (SR != SA); // same as ADD with B=1
    } break;

    default: R = 0; C = 0; V = 0; break;
    }

    Z = (R == 0);
    N = R[7];
}
