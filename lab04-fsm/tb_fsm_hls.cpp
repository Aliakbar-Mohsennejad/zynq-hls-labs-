#include <iostream>
#include "fsm_hls.h"

static void step(bool reset, bool start, ap_uint<2> mode, bool sel_mux,
                 ap_uint<32> in_data, ap_uint<32> const_data)
{
    ap_uint<32> mux_out; ap_uint<2> status;
    fsm_hls(reset, start, mode, sel_mux, in_data, const_data, mux_out, status);
    std::cout << "reset=" << reset
              << " start=" << start
              << " mode="  << (unsigned)mode
              << " sel="   << sel_mux
              << " -> status=" << (unsigned)status
              << " mux_out=" << (unsigned)mux_out << "\n";
}

int main() {
    // reset
    step(true,  false, 0, 0, 0, 0x00000000);
    // LOAD 42
    step(false, true,  1, 0, 42, 0x00000000); // take mode=LOAD
    step(false, false, 1, 1, 42, 0xAAAA5555); // hold; sel=1 -> counter shown
    // UP_COUNT two times
    step(false, true,  2, 1, 0, 0);           // mode=UP
    step(false, false, 2, 1, 0, 0);           // +1
    step(false, false, 2, 1, 0, 0);           // +1
    // DOWN_COUNT once
    step(false, true,  3, 1, 0, 0);           // mode=DOWN
    step(false, false, 3, 1, 0, 0);           // -1
    // IDLE
    step(false, true,  0, 1, 0, 0);           // mode=IDLE
    step(false, false, 0, 1, 0, 0);           // counter -> 0

    return 0;
}
