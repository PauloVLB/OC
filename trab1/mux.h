#include <iostream>
#include "systemc.h"

SC_MODULE(mux) {
	sc_in<sc_uint<32>> in1, in2;
    sc_in<bool> choose;

    sc_out<sc_uint<32>> out;

    void do_mux() {
        if(choose == 1) {
            out = in1.read();
        } else {
            out = in2.read();
        }
    }

	SC_CTOR(mux){
		SC_METHOD(do_mux);
		sensitive << in1 << in2 << choose;
	}
};