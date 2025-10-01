#include "fsm_hls.h"

enum State { IDLE=0, LOAD=1, UP_COUNT=2, DOWN_COUNT=3 };

void fsm_hls(bool reset,
             bool start,
             ap_uint<2> mode,
             bool sel_mux,
             ap_uint<32> in_data,
             ap_uint<32> const_data,
             ap_uint<32> &mux_out,
             ap_uint<2>  &status)
{
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS INTERFACE ap_none port=reset
    #pragma HLS INTERFACE ap_none port=start
    #pragma HLS INTERFACE ap_none port=mode
    #pragma HLS INTERFACE ap_none port=sel_mux
    #pragma HLS INTERFACE ap_none port=in_data
    #pragma HLS INTERFACE ap_none port=const_data
    #pragma HLS INTERFACE ap_none port=mux_out
    #pragma HLS INTERFACE ap_none port=status

    static ap_uint<32> counter = 0;
    static State       state   = IDLE;

    if (reset) {
        state   = IDLE;
        counter = 0;
    } else {
        if (start) {
            // follow mode when start=1 (IDLE/LOAD/UP/DOWN mapping)
            switch ((unsigned)mode) {
                case 0: state = IDLE;      break;
                case 1: state = LOAD;      break;
                case 2: state = UP_COUNT;  break;
                case 3: state = DOWN_COUNT;break;
                default: state = IDLE;     break;
            }
        }

        // state actions
        switch (state) {
            case IDLE:      counter = 0;              break;
            case LOAD:      counter = in_data;        break;
            case UP_COUNT:  counter = counter + 1;    break;
            case DOWN_COUNT:counter = counter - 1;    break;
        }
    }

    status = (ap_uint<2>)state;

    // MUX 2:1 (combinational)
    mux_out = sel_mux ? counter : const_data;
}
