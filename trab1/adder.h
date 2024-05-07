#include <iostream>
#include "systemc.h"

SC_MODULE(adder5) {
	sc_in<sc_uint<5>> in1, in2;
    sc_out<sc_uint<5>> out;

    void do_add() {
        out = in1.read() + in2.read();
    }

	SC_CTOR(adder5){
		SC_METHOD(do_add);
		sensitive << in1 << in2;
	}
};