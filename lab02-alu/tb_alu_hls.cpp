#include <iostream>
#include <bitset>
#include "alu_hls.h"

static void print_u8_bin(ap_uint<8> v, const char* label) {
    std::cout << label << "=" << (unsigned)v
              << " (" << std::bitset<8>(v) << ")";
}

static void run_case(ap_uint<8> A, ap_uint<8> B) {
    for (int op = 0; op <= 6; ++op) {
        ap_uint<8> R; bool C, Z, N, V;
        alu_hls_ex(A, B, (ap_uint<3>)op, R, C, Z, N, V);

        print_u8_bin(A, "A"); std::cout << "  ";
        print_u8_bin(B, "B"); std::cout << "  ";
        std::cout << "op=" << op << "  ";
        print_u8_bin(R, "R");
        std::cout << "  C=" << C
                  << "  Z=" << Z
                  << "  N=" << N
                  << "  V=" << V << "\n";
    }
}

int main() {
    run_case(0xFF, 0x80);
    run_case(0x0A, 0x02);
    run_case(0x96, 0xAD);
    run_case(0x02, 0x0A); // SUB negative example
    return 0;
}
