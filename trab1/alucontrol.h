#include <iostream>
#include "systemc.h"

SC_MODULE(alucontrol) {
    // TODO: Ver se esses 0b00 blablabla funciona mesmo, tenho a impressão qeu ja deu errado uma vez
    // In
	sc_in<sc_uint<6>> function_code;
    sc_in<sc_uint<2>> ALUOp;

    // Out
    sc_out<sc_uint<3>> op;


	void decode_op() {
        sc_uint<4> result_op = 0;
        if(ALUOp.read() == 0b00){ // Add
            result_op = 5;
        }
        else if(ALUOp.read() == 0b01){ // Subtract
            result_op = 6;
        }
        else{

            if(function_code.read() == 0b100000){ // Add
                result_op = 5;
            }else if(function_code.read() == 0b100010){ // Subtract
                result_op = 6;
            }else if(function_code.read() == 0b100100){ // AND
                result_op = 0;
            }else if(function_code.read() == 0b100101){ // OR
                result_op = 1;
            }else if(function_code.read() == 0b101010){ // Set on less then
                result_op = 4;
            }else if(function_code.read() == 0b100110){ // XOR
                result_op = 2;
            }else if(function_code.read() == 0b100111){ // NOT
                result_op = 3;
            }
        }

        op = result_op;
	}

	SC_CTOR(alucontrol) {
		SC_METHOD(decode_op);
		sensitive << function_code << ALUOp; // TODO: Eh isso memo?
	}
};