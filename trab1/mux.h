#include <iostream>
#include "systemc.h"

SC_MODULE(mux5) {
	sc_in<sc_uint<5>> in1, in2;
    sc_in<bool> choose;

    sc_out<sc_uint<5>> out;

    void do_mux() {
        if(choose == 0) {
            out = in1.read();
        } else {
            out = in2.read();
        }
    }

	SC_CTOR(mux5){
		SC_METHOD(do_mux);
		sensitive << in1 << in2 << choose;
	}
};

SC_MODULE(mux32) {
	sc_in<sc_int<32>> in1, in2;
    sc_in<bool> choose;

    sc_out<sc_int<32>> out;

    void do_mux() {
        if(choose == 0) {
            out = in1.read();
        } else {
            out = in2.read();
        }
    }

	SC_CTOR(mux32){
		SC_METHOD(do_mux);
		sensitive << in1 << in2 << choose;
	}
};