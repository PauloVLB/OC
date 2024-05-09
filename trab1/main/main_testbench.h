#include "systemc.h"

SC_MODULE(main_testbench){
    sc_in<bool> Clk;

    int i = 0;
    void TbGen() {
        
        std::cout << "Testbench started" << std::endl;
        for(int i=0; i < 160; ++i){
            std::cout << "Clock: " << i << std::endl;
            wait();
        }

        sc_stop();
    }

    SC_CTOR(main_testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};