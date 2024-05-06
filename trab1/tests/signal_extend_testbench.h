#include "systemc.h"

#define SOMA 0b101
#define SUBTRAI 0b110
#define AND 0b000

SC_MODULE(signal_extend_testbench){
    sc_in<bool> Clk;

    sc_out<sc_uint<16>> in;

    void TbGen() {

        wait(); 

        in.write(2);


        wait(); 

        in.write(4);


        wait();

        in.write(8);

        
        wait(); 

        in.write(3);
    
        wait();

        sc_stop();
    }

    SC_CTOR(signal_extend_testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};