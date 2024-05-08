#include <iostream>
#include <vector>
#include "systemc.h"

SC_MODULE(bankreg) {
    sc_in<bool> clk;

	sc_bv<32> reg[32];

    sc_in<sc_uint<5>> reg_in[2];
    sc_in<sc_uint<5>> reg_wrt;   
    sc_in<sc_int<32>> WD;
    sc_in<bool> WE;
    
    sc_out<sc_int<32>> reg_out[2];
    
    void write() {
        if(clk.read() == 0 && WE.read()) {
            reg[reg_wrt.read()] = WD.read();
            std::cout << "reg[" << reg_wrt.read() << "] = " << reg[reg_wrt.read()] << std::endl;
            std::cout << "No write do bankreg." << std::endl;
            for(int i = 0; i < 13; i++) {
                std::cout << "reg[" << i << "] = " << reg[i] << std::endl;
            }
        }
    }

    void read() {
        
        // TODO: Ta certo isso ae???
        reg_out[0] = reg[reg_in[0].read()];
        reg_out[1] = reg[reg_in[1].read()];
        // std::cout << "reg_out[0] = " << reg_out[0] << std::endl;
        // std::cout << "reg_out[1] = " << reg_out[1] << std::endl;
        

        std::cout << "No read do bankreg." << std::endl;
        for(int i = 0; i < 13; i++) {
            std::cout << "reg[" << i << "] = " << reg[i] << std::endl;
        }
    }

	SC_CTOR(bankreg) {
        for(int i = 0; i < 5; i++) {
            reg[i] = i;
        }
		SC_METHOD(write);
		sensitive << clk.neg();

        SC_METHOD(read);
        sensitive << reg_in[0] << reg_in[1];
	}
};