#include "systemc.h"

#define SOMA 0b101
#define SUBTRAI 0b110
#define AND 0b000

SC_MODULE(buffer1_testbench){
    sc_in<bool> Clk;

    sc_out<sc_uint<5>> next_instruction_adress_in;
    sc_out<sc_uint<32>> instruction_data_in;

    void TbGen() {

        wait(); 

        next_instruction_adress_in.write(12);
        instruction_data_in.write(0b10011100100101001010010110111111);


        wait(); 

        next_instruction_adress_in.write(24);
        instruction_data_in.write(14);


        wait();

        next_instruction_adress_in.write(5);
        instruction_data_in.write(2);

        
        wait(); 

        next_instruction_adress_in.write(1);
        instruction_data_in.write(1);
    
        wait();

        sc_stop();
    }

    SC_CTOR(buffer1_testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};