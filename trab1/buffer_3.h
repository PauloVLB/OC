#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_3) {
    // In
    sc_in<bool> clk;
    sc_in<sc_uint<5>> add_result_in; // What is this???????
    sc_in<bool> ula_zero_in;
    sc_in<sc_int<32>> ula_result_in;
    sc_in<sc_int<32>> reg_data_2_in;
    sc_in<sc_uint<5>> some_instruction_in; // [20 - 16] or [15 - 11]
    sc_in<bool> WB_in[2]; // RegWrite, MemtoReg
    sc_in<bool> M_in[3]; // PcSrc, MemRead, MemWrite

    // Out
    sc_out<sc_uint<5>> add_result_out; // What is this???????
    sc_out<bool> ula_zero_out;
    sc_out<sc_int<32>> ula_result_out;
    sc_out<sc_int<32>> reg_data_2_out;
    sc_out<sc_uint<5>> some_instruction_out; // [20 - 16] or [15 - 11]
    sc_out<bool> WB_out[2]; // RegWrite, MemtoReg
    sc_out<bool> M_out[3]; // PcSrc, MemRead, MemWrite

    // Registers
    sc_bv<5> add_result; // Maybe change this size
    bool ula_zero;
    sc_bv<32> ula_result;
    sc_bv<32> reg_data_2;
    sc_bv<5> some_instruction;
    bool WB[2]; // Control
    bool M[3];

    void write(){
        if(clk.read() == 0){
		    add_result = add_result_in.read();
            ula_zero = ula_zero_in.read();
            ula_result = ula_result_in.read();
            reg_data_2 = reg_data_2_in.read();
            some_instruction = some_instruction_in.read();
            WB[0] = WB_in[0].read();
            WB[1] = WB_in[1].read();
            M[0] = M_in[0].read();
            M[1] = M_in[1].read();
            M[2] = M_in[2].read();
        }
    }

    void read(){
        if(clk.read() == 1){
            add_result_out = add_result;
            ula_zero_out = ula_zero;
            ula_result_out = ula_result;
            reg_data_2_out = reg_data_2;
            some_instruction_out = some_instruction;
            WB_out[0] = WB[0];
            WB_out[1] = WB[1];
            M_out[0] = M[0];
            M_out[1] = M[1];
            M_out[2] = M[2];
        }
	}

	SC_CTOR(buffer_3){
		SC_METHOD(write);
		sensitive << clk.neg();

        SC_METHOD(read);
        sensitive << clk.pos();
	}
};