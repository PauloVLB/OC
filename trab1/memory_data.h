#include <iostream>
#include "systemc.h"

SC_MODULE(dmem) {
	sc_in<sc_int<4>> address;    // TODO: Mudar pro tamanho certo
    sc_in<sc_int<4>> write_data;// TODO: Mudar pro tamanho certo
    sc_in<bool> mem_read;
    sc_in<bool> mem_write;

    sc_out<sc_int<4>> read_data;// TODO: Mudar pro tamanho certo


    sc_bv<4> memory[4];

    void write() {
        if(clk.read() == 1 && mem_write.read()) {
            memory[address.read()] = write_data.read(); // TODO: memory é bv, mas write data é sc_int. Funciona?
        }
    }

    void read() {
        if(clk.read() == 0 && mem_read.read()) {
            read_data = memory[address.read()]; // TODO: memory é bv, mas read data é sc_int. Funciona?
        }
    }

    SC_CTOR(dm){
		int i;
		for(i=0;i<4;i++)
			memory[i]=12; // Inicializa a memória
		SC_METHOD(read);
			sensitive << address;
		SC_METHOD(write);
			sensitive << clk;
	}
};