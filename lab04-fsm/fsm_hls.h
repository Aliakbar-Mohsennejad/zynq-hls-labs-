#ifndef FSM_HLS_H
#define FSM_HLS_H

#include <ap_int.h>

// States: 0=IDLE, 1=LOAD, 2=UP_COUNT, 3=DOWN_COUNT
// sel_mux: 0 -> select const_data, 1 -> select counter
void fsm_hls(bool reset,
             bool start,
             ap_uint<2> mode,
             bool sel_mux,
             ap_uint<32> in_data,
             ap_uint<32> const_data,
             ap_uint<32> &mux_out,
             ap_uint<2>  &status);

#endif
