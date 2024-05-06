#include "systemc.h"

SC_MODULE(instruction_decoder) {
    sc_in<sc_uint<32>> instr;
    sc_out<sc_uint<6>> opcode;
    sc_out<sc_uint<5>> rs;
    sc_out<sc_uint<5>> rt;
    sc_out<sc_uint<5>> rd;
    // sc_out<sc_uint<5>> shamt;
    // sc_out<sc_uint<6>> funct;
    sc_out<sc_uint<6>> rd_shamt_funct;

    void decode() {
        opcode.write(instr.read().range(31, 26));
        rs.write(instr.read().range(25, 21));
        rt.write(instr.read().range(20, 16));
        rd.write(instr.read().range(15, 11));
        // shamt.write(instr.read().range(10, 6));
        // funct.write(instr.read().range(5, 0));
        rd_shamt_funct.write(instr.read().range(15, 0));
    }

    SC_CTOR(instruction_decoder) {
        SC_METHOD(decode);
        sensitive << instr;
    }
};