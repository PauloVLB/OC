#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_1) {
    // In
    sc_in<bool> clk;
    sc_in<sc_uint<32>> next_instruction_adress_in; // Maybe change this size
    sc_in<sc_uint<32>> instruction_data_in;

    // Out
    sc_out<sc_uint<32>> next_instruction_adress_out; // Maybe change this size
    sc_out<sc_uint<32>> instruction_data_out;

    // Registers
    sc_bv<32> next_instruction_adress; // Maybe change this size
    sc_bv<32> instruction_data;

    void write(){
        if(clk.read() == 1){
            next_instruction_adress = next_instruction_adress_in.read();
		    instruction_data = instruction_data_in.read();
        }
    }

    void read(){
        if(clk.read() == 0){
            next_instruction_adress_out = next_instruction_adress;
            instruction_data_out = instruction_data;
        }
	}

	SC_CTOR(buffer_1){
		SC_METHOD(write);
		sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << clk.neg();
	}
};