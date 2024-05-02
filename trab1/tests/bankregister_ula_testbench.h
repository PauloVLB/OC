#include "systemc.h"

#define SOMA 0b101
#define SUBTRAI 0b110
#define AND 0b000

SC_MODULE(bankregister_ula_testbench){
    sc_in<bool> Clk;

    sc_out<sc_uint<3>> op;

    sc_out<sc_uint<5>> reg_in[2];
    sc_out<sc_uint<5>> reg_wrt;   
    sc_out<sc_int<32>> WD;
    sc_out<bool> WE;

    void TbGen() {

        wait(); 

        WE.write(true);

        reg_wrt.write(3);
        WD.write(42);

        wait(); 

        reg_wrt.write(4);
        WD.write(2);

        wait();

        reg_in[0].write(3);
        reg_in[1].write(4);
        
        wait(); 
        
        WE.write(false);
        op.write(SOMA);

        wait();

        sc_stop();
    }

    SC_CTOR(bankregister_ula_testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};