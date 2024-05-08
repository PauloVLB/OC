#include <iostream>
#include <vector>
#include "systemc.h"

/// Instruction format:
/// 31-26: opcode
/// 25-21: rs
/// 20-16: rt
/// 15-11: rd
/// 10-6: shamt
/// 5-0: funct
///
/// R-type:
/// opcode= 0b000001
/// funct = 0b100000 (add)
/// funct = 0b100010 (sub)
/// funct = 0b100100 (and)
/// funct = 0b100101 (or)
/// funct = 0b101010 (slt)
/// funct = 0b100110 (xor)
/// funct = 0b100111 (nor)
///
/// I-type:
/// opcode = 0b100011 (lw)
/// opcode = 0b101011 (sw)
/// opcode = 0b000100 (beq)
/// opcode = 0b000111 (bne)
///
/// J-type:
/// opcode = 0b111111 (j)
///
/// No op:
/// opcode = 0b000000 (nop)
/// This performs an addi $0, $0, 0
///
/// Addi:
/// opcode = 0b000010 (addi)


SC_MODULE(control) {
    // sc_in<bool> clk;

    sc_in<sc_uint<6>> opcode;
    sc_out<bool> RegDst, AluSrc, Branch[2], MemRd, MemWrt, RegWrt, MemToReg;
    sc_out<bool> AluOp[2];

    void do_control() {
        sc_uint<6> opcode_val = opcode.read();
        switch (opcode_val) {
            case 0b000000: // No op
                RegDst = 0;
                AluSrc = 1;
                Branch[0] = 0;
                Branch[1] = 0;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 0;
                MemToReg = 0;
                // AluOp = 0b10;
                AluOp[0] = 0;
                AluOp[1] = 0;
                break;
            case 0b000001: // R-type
                RegDst = 1;
                AluSrc = 0;
                Branch[0] = 0;
                Branch[1] = 0;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 1;
                MemToReg = 0;
                // AluOp = 0b10;
                AluOp[0] = 1;
                AluOp[1] = 0;
                break;
            case 0b000010: // addi
                RegDst = 0;
                AluSrc = 1;
                Branch[0] = 0;
                Branch[1] = 0;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 1;
                MemToReg = 0;
                // AluOp = 0b10;
                AluOp[0] = 0;
                AluOp[1] = 0;
                break;
            case 0b100011: // lw
                RegDst = 0;
                AluSrc = 1;
                Branch[0] = 0;
                Branch[1] = 0;
                MemRd = 1;
                MemWrt = 0;
                RegWrt = 1;
                MemToReg = 1;
                // AluOp = 0b00;
                AluOp[0] = 0;
                AluOp[1] = 0;
                break;
            case 0b101011: // sw
                RegDst = 0;
                AluSrc = 1;
                Branch[0] = 0;
                Branch[1] = 0;
                MemRd = 0;
                MemWrt = 1;
                RegWrt = 0;
                MemToReg = 0;
                // AluOp = 0b00;
                AluOp[0] = 0;
                AluOp[1] = 0;
                break;
            case 0b000100: // beq
                RegDst = 0;
                AluSrc = 0;
                Branch[0] = 0;
                Branch[1] = 1;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 0;
                MemToReg = 0;
                // AluOp = 0b01;
                AluOp[0] = 0;
                AluOp[1] = 1;
                break;
            case 0b000111: // bne
                RegDst = 0;
                AluSrc = 0;
                Branch[0] = 1;
                Branch[1] = 0;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 0;
                MemToReg = 0;
                // AluOp = 0b01;
                AluOp[0] = 0;
                AluOp[1] = 1;
                break;
            case 0b111111: // j
                RegDst = 0;
                AluSrc = 0;
                Branch[0] = 1;
                Branch[1] = 1;
                MemRd = 0;
                MemWrt = 0;
                RegWrt = 0;
                MemToReg = 0;
                // AluOp = 0b00;
                AluOp[0] = 0;
                AluOp[1] = 0;
                break;
            default:
                std::cout << "Invalid opcode: " << opcode_val << std::endl;
                break;
        }
    }

    SC_CTOR(control) {
        SC_METHOD(do_control);
        // sensitive << clk.pos(); // TODO: Sensitive a opcode tambem?
        sensitive << opcode;
    }
};