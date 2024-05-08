#include "systemc.h"

SC_MODULE(branch_component){

    // Signal for branch
    // 00 = No branch
    // 01 = Branch if equal
    // 10 = Branch if not equal
    // 11 = Jump
    sc_in<bool> Branch[2];
    sc_in<bool> zero;

    sc_out<bool> PCSrc;

    void do_branch(){
        if(Branch[0].read() == 0 && Branch[1].read() == 1 && zero.read() == 1){
            PCSrc = 1;
        }
        else if(Branch[0].read() == 1 && Branch[1].read() == 0 && zero.read() == 0){
            PCSrc = 1;
        } else if(Branch[0].read() == 1 && Branch[1].read() == 1){
            PCSrc = 1;
        }
        else{
            PCSrc = 0;
        }
    }

    SC_CTOR(branch_component){
        SC_METHOD(do_branch);
        sensitive << Branch[0] << Branch[1] << zero;
    }

};