#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_4) {
    // In
    sc_in<bool> clk;
    sc_in<sc_int<32>> memory_data_in;
    sc_in<sc_int<32>> ula_result_in;
    sc_in<sc_uint<5>> some_instruction_in; // [20 - 16] or [15 - 11]

    // Out
    sc_out<sc_int<32>> memory_data_out;
    sc_out<sc_int<32>> ula_result_out;
    sc_out<sc_uint<5>> some_instruction_out; // [20 - 16] or [15 - 11]

    // Registers
    sc_bv<32> memory_data;
    sc_bv<32> ula_result;
    sc_bv<5> some_instruction;

    void write(){
        if(clk.read() == 1){
		    add_result = add_result_in.read();
            ula_result = ula_result_in.read();
            some_instruction = some_instruction_in.read();
        }
    }

    void read(){
        if(clk.read() == 0){
            add_result_out = add_result;
            ula_result_out = ula_result;
            some_instruction_out = some_instruction;
        }
	}

	SC_CTOR(buffer_4){
		SC_METHOD(write);
		sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << clk.neg();
	}
};