#include <iostream>
#include "systemc.h"

SC_MODULE(imem) {
	sc_in<sc_uint<5>> instruction_address;// TODO: Mudar pro tamanho certo
    sc_out<sc_uint<32>> instruction_data;// TODO: Mudar pro tamanho certo

    sc_bv<32> memory[32];// TODO: Mudar pro tamanho certo

    void read(){
		instruction_data = memory[instruction_address.read()];// No do amigão não tem esse .read()
	}

	SC_CTOR(imem){
		for(int i=0; i < 32; ++i){
			memory[i] = 0;
		}
		SC_METHOD(read);
		sensitive << instruction_address;
	}
};