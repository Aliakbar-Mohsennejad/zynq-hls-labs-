#include <iostream>
#include <bitset>
#include "regbank_hls.h"

static void print_u8_bin(ap_uint<8> v, const char* lbl) {
    std::cout << lbl << "=" << (unsigned)v
              << " (" << std::bitset<8>(v) << ")";
}

int main() {
    ap_uint<8> out;

    // --- Writes: addr=10->0xAA, 20->0xBB, 30->0xCC ---
    regbank_hls(10, 0xAA, /*write=*/true,  /*read=*/false, /*enable=*/true, out);
    regbank_hls(20, 0xBB, /*write=*/true,  /*read=*/false, /*enable=*/true, out);
    regbank_hls(30, 0xCC, /*write=*/true,  /*read=*/false, /*enable=*/true, out);

    // --- Reads (like the SystemC flow) ---
    regbank_hls(10, 0x00, /*write=*/false, /*read=*/true,  /*enable=*/true, out);
    print_u8_bin(10, "addr"); std::cout << "  "; print_u8_bin(out, "data"); std::cout << "\n";

    regbank_hls(20, 0x00, /*write=*/false, /*read=*/true,  /*enable=*/true, out);
    print_u8_bin(20, "addr"); std::cout << "  "; print_u8_bin(out, "data"); std::cout << "\n";

    regbank_hls(30, 0x00, /*write=*/false, /*read=*/true,  /*enable=*/true, out);
    print_u8_bin(30, "addr"); std::cout << "  "; print_u8_bin(out, "data"); std::cout << "\n";

    return 0;
}
