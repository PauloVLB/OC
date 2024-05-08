#include <iostream>
#include "systemc.h"

SC_MODULE(buffer_1) {
    // In
    sc_in<bool> clk;
    // sc_in<sc_uint<5>> next_instruction_adress_in; // Maybe change this size
    sc_in<sc_uint<32>> instruction_data_in;

    // Out
    // sc_out<sc_uint<5>> next_instruction_adress_out; // Maybe change this size
    // sc_out<sc_uint<32>> instruction_data_out;
    sc_out<sc_uint<6>> opcode_out;
    sc_out<sc_uint<5>> rs_out;
    sc_out<sc_uint<5>> rt_out;
    sc_out<sc_uint<5>> rd_out;
    sc_out<sc_uint<16>> rdShamtFunct_out;

    // Registers
    // sc_bv<5> next_instruction_adress; // Maybe change this size
    sc_bv<6> opcode;
    sc_bv<5> rs;
    sc_bv<5> rt;
    sc_bv<5> rd;
    sc_bv<16> rdShamtFunct;

    void write(){
        if(clk.read() == 1){
            // next_instruction_adress = next_instruction_adress_in.read();
		    // instruction_data = instruction_data_in.read();
            opcode = instruction_data_in.read().range(31, 26);
            rs = instruction_data_in.read().range(25, 21);
            rt = instruction_data_in.read().range(20, 16);
            rd = instruction_data_in.read().range(15, 11);
            rdShamtFunct = instruction_data_in.read().range(15, 0);
        }
    }

    void read(){
        if(clk.read() == 0){
            // next_instruction_adress_out = next_instruction_adress;
            // instruction_data_out = instruction_data;
            opcode_out = opcode;
            rs_out = rs;
            rt_out = rt;
            rd_out = rd;
            rdShamtFunct_out = rdShamtFunct;
        }
	}

	SC_CTOR(buffer_1){
		SC_METHOD(write);
		sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << clk.neg();
	}
};