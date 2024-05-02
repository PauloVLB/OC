#include "systemc.h"

SC_MODULE(bankregister_ula_testbench){
    sc_in<bool> Clk;

    sc_out<sc_int<32>> A, B;
    sc_out<sc_uint<3>> op;

    sc_out<sc_uint<5>> reg_in[2];
    sc_out<sc_uint<5>> reg_wrt;   
    sc_out<sc_int<32>> WD;
    sc_out<bool> WE;
    
    sc_out<sc_int<32>> reg_out[2];

    void TbGen() {
        WE.write(true);

        reg_wrt.write(3);
        WD.write(42);

        wait(); 

        reg_wrt.write(4);
        WD.write(2);

        wait();

        WE.write(false);

        reg_in[0].write(2);
        reg_in[1].write(42);
        
        // wait(); 

        A.write(reg_out[0]);
        B.write(reg_out[1]);
        op.write(SOMA);

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
}