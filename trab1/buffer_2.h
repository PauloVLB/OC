#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_2) {
    // In
    sc_in<bool> clk;
    sc_in<sc_uint<32>> next_instruction_adress_in; // Maybe change this size
    sc_in<sc_int<32>> reg_data_1_in;
    sc_in<sc_int<32>> reg_data_2_in;
    sc_in<sc_uint<32>> instruction_1_in; // [15 - 0], but extended (size 32?)
    sc_in<sc_uint<5>> instruction_2_in; // [20 - 16]
    sc_in<sc_uint<5>> instruction_3_in; // [15 - 11]
    sc_in<bool> WB_in, M_in, EX_in; // Control

    // Out
    sc_out<sc_uint<32>> next_instruction_adress_out; // Maybe change this size
    sc_out<sc_int<32>> reg_data_1_out;
    sc_out<sc_int<32>> reg_data_2_out;
    sc_out<sc_uint<32>> instruction_1_out; // [15 - 0], but extended (size 32?)
    sc_out<sc_uint<5>> instruction_2_out; // [20 - 16]
    sc_out<sc_uint<5>> instruction_3_out; // [15 - 11]
    sc_out<bool> WB_out, M_out, EX_out; // Control

    // Registers
    sc_bv<32> next_instruction_adress; // Maybe change this size
    sc_bv<32> reg_data_1;
    sc_bv<32> reg_data_2;
    sc_bv<32> instruction_1;
    sc_bv<5> instruction_2;
    sc_bv<5> instruction_3;
    bool WB, M, EX; // Control

    void write(){
        if(clk.read() == 1){
		    next_instruction_adress = next_instruction_adress_in.read();
            reg_data_1 = reg_data_1_in.read();
            reg_data_2 = reg_data_2_in.read();
            instruction_1 = instruction_1_in.read();
            instruction_2 = instruction_2_in.read();
            instruction_3 = instruction_3_in.read();
            WB = WB_in.read();
            M = M_in.read();
            EX = EX_in.read();
        }
    }

    void read(){
        if(clk.read() == 0){
            next_instruction_adress_out = next_instruction_adress;
            reg_data_1_out = reg_data_1;
            reg_data_2_out = reg_data_2;
            instruction_1_out = instruction_1;
            instruction_2_out = instruction_2;
            instruction_3_out = instruction_3;
            WB_out = WB_data;
            M_out = M;
            EX_out = EX;
        }
	}

	SC_CTOR(buffer_2){
		SC_METHOD(write);
		sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << clk.neg();
	}
};