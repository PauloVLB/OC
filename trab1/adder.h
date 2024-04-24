#include <iostream>
#include "systemc.h"

SC_MODULE(adder) {
	sc_in<sc_uint<32>> in1, in2;
    sc_out<sc_uint<32>> out;

    void do_add() {
        out = in1.read() + in2.read();
    }

	SC_CTOR(adder){
		SC_METHOD(do_add);
		sensitive << in1 << in2;
	}
};