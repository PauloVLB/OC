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
        std::cout << "No write do pc:" << instruction_address_in.read();
        std::cout << " Curr_instruction = " << curr_instruction << std::endl;
    }

    void read(){
        sc_uint<5> adress_out;
        if(clk.read() == 1) {
            if(first){
                instruction_address_out = 0;
                adress_out = 0;
                first = false;
            }
            else{
                adress_out = curr_instruction;
                instruction_address_out = curr_instruction;
            }
        }
        std::cout << "No read do pc. Curr_instruction = " << curr_instruction << ". Adress_out = " << adress_out << std::endl;
	}

	SC_CTOR(pc){
        first = true;
		SC_METHOD(write);
			sensitive << clk.neg();
		SC_METHOD(read);
			sensitive << clk.pos();
	}
};