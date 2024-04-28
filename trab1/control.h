#include <iostream>
#include <vector>
#include "systemc.h"

SC_MODULE(control) {
    sc_in<bool> clk;

    sc_in<sc_uint<32>> instr;
    sc_out<bool> RegDst, AluSrc, Branch, MemRd, MemWrt, RegWrt, MemToReg;
    sc_out<sc_uint<2>> AluOp; // nao sabamos
    enum states {
        INIT = 0,
        L,
        S,
        J,
        R
    }; 

    states sta = INIT;

    void controle() {
        switch (sta) {
        case INIT:
            /* empty */
            break;
        case L:
            RegDst.write(0);
            AluSrc.write(1);
            Branch.write(0);
            MemRd.write(1);
            MemWrt.write(0);
            RegWrt.write(1);
            MemToReg.write(1);
            AluOp.write(0b00);
            break;
        case S:
            //RegDst.write(X);
            AluSrc.write(1);
            Branch.write(0);
            MemRd.write(0);
            MemWrt.write(1);
            RegWrt.write(0);
            //MemToReg.write(X);
            AluOp.write(0b00);
            break;
        case J:
            //RegDst.write(0);
            AluSrc.write(0);
            Branch.write(1);
            MemRd.write(0);
            MemWrt.write(0);
            RegWrt.write(0);
            //MemToReg.write(0);
            AluOp.write(0b01);
            break;
        case R:
            RegDst.write(1);
            AluSrc.write(0);
            Branch.write(0);
            MemRd.write(0);
            MemWrt.write(0);
            RegWrt.write(1);
            MemToReg.write(0);
            AluOp.write(0b10);
            break;
        default:
            break;
        }

        if(true) { // instrução tipo R
            sta = R;
        } else if(true) {
            sta = J;
        } else if(true) {
            sta = L;
        } else if (true) {
            sta = S;
        } else {
            sta = INIT;
        }
    }
	SC_CTOR(control) {
		/* SC_METHOD(write);
		sensitive << clk;

        SC_METHOD(read);
        sensitive << reg_in[0] << reg_in[1]; */
	}
};