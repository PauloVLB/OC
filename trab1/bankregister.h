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
            // std::cout << "reg[" << reg_wrt.read() << "] = " << reg[reg_wrt.read()] << std::endl;
            std::cout << "No write do bankreg." << std::endl;
            for(int i = 0; i < 4; i++) {
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
        

        // std::cout << "No read do bankreg." << std::endl;
        // for(int i = 0; i < 12; i++) {
        //     std::cout << "reg[" << i << "] = " << reg[i] << std::endl;
        // }
    }

	SC_CTOR(bankreg) {
        /// Algoritmo 1 -- Perfeito
		// Pre-Processamento:
		// $reg0 = 0, $reg1 = 1, $reg2 = 2, $reg3 = 3, $reg4 = 4, $reg5 = 5, $reg6 = 6, 
		// $reg7 = 7, $reg8 = 8, $reg9 = 9, $reg10 = 10, $reg11 = 11
        // for(int i = 0; i < 12; i++) {
        //     reg[i] = i;
        // }
		SC_METHOD(write);
		sensitive << clk.neg();

        SC_METHOD(read);
        sensitive << reg_in[0] << reg_in[1];
	}
};