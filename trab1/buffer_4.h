#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_4) {
    // In
    sc_in<bool> clk;
    sc_in<sc_int<32>> memory_data_in;
    sc_in<sc_int<32>> ula_result_in;
    sc_in<sc_uint<5>> some_instruction_in; // [20 - 16] or [15 - 11]
    sc_in<bool> WB_in[2]; // RegWrite, MemtoReg

    // Out
    sc_out<sc_int<32>> memory_data_out;
    sc_out<sc_int<32>> ula_result_out;
    sc_out<sc_uint<5>> some_instruction_out; // [20 - 16] or [15 - 11]
    sc_out<bool> WB_out[2]; // RegWrite, MemtoReg

    // Registers
    sc_bv<32> memory_data;
    sc_bv<32> ula_result;
    sc_bv<5> some_instruction;
    bool WB[2]; // Control

    void write(){
        if(clk.read() == 0){
		    memory_data = memory_data_in.read();
            ula_result = ula_result_in.read();
            some_instruction = some_instruction_in.read();
            WB[0] = WB_in[0].read();
            WB[1] = WB_in[1].read();
        }
    }

    void read(){
        if(clk.read() == 1){
            memory_data_out = memory_data;
            ula_result_out = ula_result;
            some_instruction_out = some_instruction;
            WB_out[0] = WB[0];
            WB_out[1] = WB[1];
        }
	}

	SC_CTOR(buffer_4){
		SC_METHOD(write);
		sensitive << clk.neg();

        SC_METHOD(read);
        sensitive << clk.pos();
	}
};