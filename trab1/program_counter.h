#include <iostream>
#include "systemc.h"

SC_MODULE(pc) {
	sc_in<sc_uint<32>> instruction_address;// TODO: Mudar pro tamanho certo
    sc_out<sc_uint<32>> instruction_data;// TODO: Mudar pro tamanho certo

    sc_clock clk;

    sc_bv<32> curr_instruction;// TODO: Mudar pro tamanho certo

    void write() {
        if(clk.read() == 0 && instruction_address.read()) {
            curr_instruction = instruction_data.read(); // TODO: memory é bv, mas write data é sc_int. Funciona?
        }
    }

    void read(){
        if(clk.read() == 1) {
            instruction_data = curr_instruction;
        }
	}

	SC_CTOR(pc){
		SC_METHOD(read);
			sensitive << instruction_address;
		SC_METHOD(write);
			sensitive << clk;
	}
};