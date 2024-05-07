#include <iostream>
#include "systemc.h"

SC_MODULE(sign_ext) {
	sc_in<sc_uint<16>> in;
    sc_out<sc_int<32>> out;

    void do_ext() {
		
		out.write((int)(int16_t)in.read());
    }

	SC_CTOR(sign_ext){
		SC_METHOD(do_ext);
		sensitive << in;
	}
};