#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_3) {
    // In
    sc_in<bool> clk;
    sc_in<sc_uint<32>> add_result_in; // What is this???????
    sc_in<bool> ula_zero_in;
    sc_in<sc_int<32>> ula_result_in;
    sc_in<sc_int<32>> reg_data_2_in;
    sc_in<sc_uint<5>> some_instruction_in; // [20 - 16] or [15 - 11]
    sc_in<bool> WB_in, M_in; // Control

    // Out
    sc_out<sc_uint<32>> add_result_out; // What is this???????
    sc_out<bool> ula_zero_out;
    sc_out<sc_int<32>> ula_result_out;
    sc_out<sc_int<32>> reg_data_2_out;
    sc_out<sc_uint<5>> some_instruction_out; // [20 - 16] or [15 - 11]
    sc_out<bool> WB_out, M_out; // Control

    // Registers
    sc_bv<32> add_result; // Maybe change this size
    bool ula_zero;
    sc_bv<32> ula_result;
    sc_bv<32> reg_data_2;
    sc_bv<5> some_instruction;
    bool WB, M; // Control

    void write(){
        if(clk.read() == 1){
		    add_result = add_result_in.read();
            ula_zero = ula_zero_in.read();
            ula_result = ula_result_in.read();
            reg_data_2 = reg_data_2_in.read();
            some_instruction = some_instruction_in.read();
            WB = WB_in.read();
            M = M_in.read();
        }
    }

    void read(){
        if(clk.read() == 0){
            add_result_out = add_result;
            ula_zero_out = ula_zero;
            ula_result_out = ula_result;
            reg_data_2_out = reg_data_2;
            some_instruction_out = some_instruction;
            WB_out = WB;
            M_out = M;
        }
	}

	SC_CTOR(buffer_3){
		SC_METHOD(write);
		sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << clk.neg();
	}
};