#include "systemc.h"

SC_MODULE(main_testbench){
    sc_in<bool> Clk;

    void TbGen() {

        wait(); 

        wait(); 

        wait();
        
        wait(); 

        wait();

        wait(); 

        wait(); 

        wait();
        
        wait(); 

        wait();

        wait();
        
        wait(); 

        wait();

        wait();
        
        wait(); 

        wait();

        wait();
        
        wait(); 

        wait();

        sc_stop();
    }

    SC_CTOR(main_testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};