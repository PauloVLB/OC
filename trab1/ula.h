#include <iostream>
#include "systemc.h"

SC_MODULE(ula) {
	sc_in<sc_int<32>> A, B;
    sc_in<sc_uint<3>> op;

	sc_out<bool> zero;
    sc_out<sc_int<32>> result;

	void do_op() {
        sc_int<32> A_val, B_val, res;

        A_val = A.read();
        B_val = B.read();

		switch (op.read()) {
            case 0:
                res = A_val & B_val;
                // std::cout << "Na ula, resultado de A_val: " << A_val << " AND B_val: " << B_val << " = res: " << res << std::endl;
                // std::cout << "case 0" << std::endl;
                break;
            case 1:
                res = A_val | B_val;
                // std::cout << "case 1" << std::endl;
                break;
            case 2:
                res = A_val ^ B_val;
                // std::cout << "case 2" << std::endl;
                break;
            case 3:
                res = ~A_val;
                // std::cout << "case 3" << std::endl;
                break;
            case 4:
                res = A_val < B_val;
                // std::cout << "Na ula, resultado de A_val: " << A_val << " < B_val: " << B_val << " = res: " << res << std::endl;
                // std::cout << "case 4" << std::endl;
                break;
            case 5:
                res = A_val + B_val;
                // std::cout << "Na ula, resultado de A_val: " << A_val << " + B_val: " << B_val << " = res: " << res << std::endl;
                // std::cout << "case 5" << std::endl;
                break;
            case 6:
                res = A_val - B_val;
                // std::cout << "Na ula, resultado de A_val: " << A_val << " - B_val: " << B_val << " = res: " << res << std::endl;
                // std::cout << "case 6" << std::endl;
                break;
            default:
                res = 32;
                std::cout << "default????" << std::endl;
                break;
        }

        result.write(res);
        if(res == 0) {
            zero = 1;
        }
        else{
            zero = 0;
        }
	}

	SC_CTOR(ula) {
		SC_METHOD(do_op);
		sensitive << A << B << op;
	}
};