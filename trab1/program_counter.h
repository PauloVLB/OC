#include <iostream>
#include "systemc.h"

SC_MODULE(pc) {
    sc_in<bool> clk;
	sc_in<sc_uint<5>> instruction_address_in;// TODO: Mudar pro tamanho certo
    sc_out<sc_uint<5>> instruction_address_out;// TODO: Mudar pro tamanho certo


    sc_bv<5> curr_instruction;// TODO: Mudar pro tamanho certo
    bool first;

    void write() {
        if(clk.read() == 0) {
            curr_instruction = instruction_address_in.read(); // TODO: memory é bv, mas write data é sc_int. Funciona?
        }
    }

    void read(){
        if(clk.read() == 1) {
            if(first){
                instruction_address_out = 0;
                first = false;
            }
            else{
                instruction_address_out = curr_instruction;
            }
        }
	}

	SC_CTOR(pc){
        first = true;
		SC_METHOD(read);
			sensitive << clk.neg();
		SC_METHOD(write);
			sensitive << clk.pos();
	}
};