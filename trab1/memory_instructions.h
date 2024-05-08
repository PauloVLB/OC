#include <iostream>
#include "systemc.h"

SC_MODULE(imem) {
	sc_in<sc_uint<5>> instruction_address;
    sc_out<sc_uint<32>> instruction_data;

    sc_bv<32> memory[32];

    void read(){
		instruction_data = memory[instruction_address.read()];// No do amigão não tem esse .read()
	}

	SC_CTOR(imem){
		for(int i=0; i < 32; ++i){
			memory[i] = 0;
		}
		/// R-TYPE Instructions
		// //            V----VV---VV---VV---VV---VV----V
		// memory[0] = 0b00001000000001010000000001000000; // 000010 (addi) 00000 ($zero)  00101 ($reg5)  64 (0000000001000000)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[1] = 0b00000100011000110011000000000000; // 000001 (R-Type)  00001 ($reg1)  00011 ($reg3)  00110 ($reg6) 00000 (shmat) 000000 (funct add)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[2] = 0b00000100001000110011100000100010; // 000001 (R-Type)  00001 ($reg1)  00011 ($reg3)  00111 ($reg7) 00000 (shmat) 100010 (funct sub)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[3] = 0b00000100010000110100000000100100; // 000001 (R-Type)  00010 ($reg2)  00011 ($reg3)  01000 ($reg8) 00000 (shmat) 100100 (funct and)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[4] = 0b00000100100000110100100000100101; // 000001 (R-Type)  00100 ($reg4)  00011 ($reg3)  01001 ($reg9) 00000 (shmat) 100101 (funct or)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[5] = 0b00000100011001000101000000101010; // 000001 (R-Type)  00011 ($reg3)  00100 ($reg4)  01010 ($reg10) 00000 (shmat) 101010 (funct slt)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[6] = 0b00000100011000100101100000100110; // 000001 (R-Type)  00011 ($reg3)  00010 ($reg2)  01011 ($reg11) 00000 (shmat) 100110 (funct xor)
		// //            V----VV---VV---VV---VV---VV----V
		// memory[7] = 0b00000100100000100110000000100111; // 000001 (R-Type)  00100 ($reg4)  00010 ($nao importa) 01100 ($reg12) 00000 (shmat) 100111 (funct not)
		
		/// JUMP Instructions
		// memory[0] = 0b11111100000000000000000000000000; // 111111 (jump) 0 (00000000000000000000000000) (endereco do jump)
		
		/// BEQ Instructions
		// memory[0] = 0b00010000000000010000000000000000; // 000100 (beq) 00000 ($zero) 00000 ($zero) 0000000000000000 (endereco do branch)

		/// BNE Instructions
		// memory[0] = 0b00011100010000010000000000001000; // 000111 (bne) 00000 ($zero) 00000 ($zero) 0000000000000000 (endereco do branch)

		SC_METHOD(read);
		sensitive << instruction_address;
	}
};

// INSTRUCOES IMMEDIATE

// no_op
// 000000 00000 00000 0
// addi   $zero $zero immediate

// addi $s0, $zero, 64
// 000010 00000  00001    64
//  addi  $zero   $s0   immediate

// INSTRUCOES TIPO R

// add $t3, $t1, $t2
// 000001 00001 00010 00011 00000 000000
// R-type $t1   $t2   $t3	 shamt funct

// sub $t3, $t1, $t2
// 000001 00001 00010 00011 00000 100010
// R-type $t1   $t2   $t3	 shamt funct

// and $t3, $t1, $t2
// 000001 00001 00010 00011 00000 100100
// R-type $t1   $t2   $t3	 shamt funct

// or $t3, $t1, $t2
// 000001 00001 00010 00011 00000 100101
// R-type $t1   $t2   $t3	 shamt funct

// slt $t3, $t1, $t2
// 000001 00001 00010 00011 00000 101010
// R-type $t1   $t2   $t3	 shamt funct

// xor $t3, $t1, $t2
// 000001 00001 00010 00011 00000 100110
// R-type $t1   $t2   $t3	 shamt funct

// not $t3, $t1, $t2
// 000001 00001 00010 00011 00000 100111
// R-type $t1   $t2   $t3	 shamt funct