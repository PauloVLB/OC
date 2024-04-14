#include "systemc.h"

#define SOMA 0b101
#define SUBTRAI 0b110
#define AND 0b000

SC_MODULE(testbench) {
    sc_in<bool> Clk;

    sc_out<sc_int<32>> A, B;
    sc_out<sc_uint<3>> op;

    void TbGen() {
        A.write(7);
        B.write(1);
        op.write(0);

        wait();

        A.write(7);
        B.write(1);
        op.write(0);

        wait();

        A.write(429);
        B.write(23);
        op.write(6);

        wait();

        A.write(1331);
        B.write(-31);
        op.write(5);

        wait();

        sc_stop();
    }

    SC_CTOR(testbench) {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};
