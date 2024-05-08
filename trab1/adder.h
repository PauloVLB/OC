#include <iostream>
#include "systemc.h"

SC_MODULE(adder5) {
	sc_in<sc_uint<5>> in1, in2;
    sc_out<sc_uint<5>> out;

    void do_add() {
		sc_uint<5> in1_val, in2_val, res;
		in1_val = in1.read();
		in2_val = in2.read();
		res = in1_val + in2_val;
		// std::cout << "No adder5: " << in1_val << " + " << in2_val << " = " << res << std::endl;
        out.write(res);
    }

	SC_CTOR(adder5){
		SC_METHOD(do_add);
		sensitive << in1 << in2;
	}
};