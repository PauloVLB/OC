#include <iostream>
#include "systemc.h"

SC_MODULE(dmem) {
	sc_in<sc_int<32>> address;
    sc_in<sc_int<32>> write_data;
    sc_in<bool> mem_read;
    sc_in<bool> mem_write;

    sc_in<bool> clk;

    sc_out<sc_int<32>> read_data;


    sc_bv<32> memory[32];

    sc_int<5> real_adress;

    void write() {
        real_adress = address.read().range(4,0);
        if(clk.read() == 0 && mem_write.read()) {
            memory[real_adress] = write_data.read(); // TODO: memory é bv, mas write data é sc_int. Funciona?
        }
    }

    void read() {
        real_adress = address.read().range(4,0);
        if(clk.read() == 1 && mem_read.read()) {
            read_data = memory[real_adress]; // TODO: memory é bv, mas read data é sc_int. Funciona?
        }
    }

    SC_CTOR(dmem){
		int i;
		for(i=0;i<32;i++)
			memory[i]=37; // Inicializa a memória a normal normalmente é 37
		SC_METHOD(read);
			sensitive << address;
		SC_METHOD(write);
			sensitive << clk;
	}
};