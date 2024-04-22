#include <iostream>
#include "systemc.h"

SC_MODULE(imem) {
	sc_in<sc_uint<4>> instruction_address;// TODO: Mudar pro tamanho certo
    sc_out<sc_uint<4>> instruction_data;// TODO: Mudar pro tamanho certo

    sc_bv<4> memory[4];// TODO: Mudar pro tamanho certo

    void read(){
		instruction_data = memory[instruction_address.read()];// No do amigão não tem esse .read()
	}

	SC_CTOR(im){
		SC_METHOD(read);
		sensitive << instruction_address;
	}
};