#include <iostream>
#include <vector>
#include "systemc.h"

SC_MODULE(bankreg) {
    sc_clock clk;

	sc_bv<4> reg[8];

    sc_in<sc_uint<4>> reg_in[2];
    sc_in<sc_uint<4>> reg_wrt;   
    sc_in<sc_int<4>> WD;
    sc_in<bool> WE;
    
    sc_out<sc_int<4>> reg_out[2];
    
    void write() {
        if(clk.read() == 1 && WE.read()) {
            reg[reg_wrt.read()] = WD.read();
        }
    }

    void read() {
        reg_out[0] = reg[reg_in[0].read()];
        reg_out[1] = reg[reg_in[1].read()];
    }

	SC_CTOR(bankreg) {
		SC_METHOD(write);
		sensitive << clk;

        SC_METHOD(read);
        sensitive << reg_in[0] << reg_in[1];
	}
};