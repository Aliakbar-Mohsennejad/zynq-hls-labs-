#include <iostream>
#include "single_intr_hls.h"

static void step(bool reset, bool interrupt, ap_uint<8> normal_in, ap_uint<8> intr_in) {
    ap_uint<8> out;
    ap_uint<2> status;
    single_intr_hls(reset, interrupt, normal_in, intr_in, out, status);
    std::cout << "reset=" << reset
              << " interrupt=" << interrupt
              << " normal_in=" << (unsigned)normal_in
              << " intr_in=" << (unsigned)intr_in
              << " -> out=" << (unsigned)out
              << " status=" << (unsigned)status << "\n";
}

int main() {
    step(true,  false, 10, 99);  // reset
    step(false, false, 10, 99);  // normal
    step(false, false, 20, 99);  // normal
    step(false, true,  30, 77);  // ISR
    step(false, true,  40, 88);  // ISR
    step(false, false, 50, 88);  // normal
    return 0;
}
