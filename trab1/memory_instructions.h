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

		/// LW Instructions
		// //            V----VV---VV---VV---VV---VV----V
		// memory[0] = 0b10001100000000010000000000000000; // 100011 (lw) 00000 ($zero) 00001 ($reg1) 0000000000000000 (offset)

		/// SW Instructions
		// //            V----VV---VV---VV---VV---VV----V
		// memory[0] = 0b10101100000000010000000000000000; // 101011 (sw) 00000 ($zero) 00001 ($reg1) 0000000000000000 (offset)

		/// Algoritmo 1 -- Perfeito
		// Pre-Processamento:
		// $reg0 = 0, $reg1 = 1, $reg2 = 2, $reg3 = 3, $reg4 = 4, $reg5 = 5, $reg6 = 6, 
		// $reg7 = 7, $reg8 = 8, $reg9 = 9, $reg10 = 10, $reg11 = 11
		
		// add $reg3, $reg1, $reg2
		// lw $reg4, 0($reg6)
		// sub $reg7, $reg8, $reg9
		// xor $reg10, $reg10, $reg11
		// sw $reg5, 10($reg0)

		/// Instructions
		// //            V----VV---VV---VV---VV---VV----V  // add $reg3, $reg1, $reg2
		// memory[0] = 0b00000100001000100001100000000000; // 000001 (R-Type)   00001 ($reg1)  00010 ($reg2)  00011 ($reg3) 00000 (shmat) 000000 (funct add)
		
		// //            V----VV---VV---VV---VV---VV----V	// lw $reg4, 0($reg6)
		// memory[1] = 0b10001100110001000000000000000000; // 100011 (lw) 00110 ($reg6) 00100 ($reg4) 0000000000000000 (offset)
		
		// //            V----VV---VV---VV---VV---VV----V	// sub $reg7, $reg8, $reg9
		// memory[2] = 0b00000101000010010011100000100010; // 000001 (R-Type)  01000 ($reg8)  01001 ($reg9)  00111 ($reg7) 00000 (shmat) 100010 (funct sub)
		
		// //            V----VV---VV---VV---VV---VV----V  // xor $reg10, $reg10, $reg11
		// memory[3] = 0b00000101010010110101000000100110; // 000001 (R-Type)  01010 ($reg10)  01011 ($reg11)  01010 ($reg10) 00000 (shmat) 100110 (funct xor)
		
		// //            V----VV---VV---VV---VV---VV----V	// sw $reg5, 10($reg0)
		// memory[4] = 0b10101100000001010000000000001010; // 101011 (sw) 00000 ($zero) 00101 ($reg5) 0000000000001010 (offset)

		/// Algoritmo 2 -- Divisão
		// addi $reg1, $zero, 15
		// addi $reg2, $zero, 5
		// addi $reg3, $zero, 0
		// ENQUANTO:
		// 	sub $reg1, $reg1, $reg2
		// 	addi $reg3, $reg3, 1
		// 	bne $reg1, $zero, ENQUANTO
		// FIM:

		/// Instructions
		//            V----VV---VV---VV---VV---VV----V  // addi $reg1, $zero, 15
		memory[0] = 0b00001000000000010000000000001111; // 000010 (addi) 00000 ($zero)  00001 ($reg1)  15 (0000000000001111)

		//            V----VV---VV---VV---VV---VV----V  // addi $reg2, $zero, 5
		memory[1] = 0b00001000000000100000000000000101; // 000010 (addi) 00000 ($zero)  00010 ($reg2)  5 (0000000000000101)

		//            V----VV---VV---VV---VV---VV----V  // addi $reg3, $zero, 0
		memory[2] = 0b00001000000000110000000000000000; // 000010 (addi) 00000 ($zero)  00011 ($reg3)  0 (0000000000000000)

		memory[3] = 0b00000000000000000000000000000000;
		memory[4] = 0b00000000000000000000000000000000;

		memory[5] = 0b00000000000000000000000000000000; // ENQUANTO

		//            V----VV---VV---VV---VV---VV----V  // sub $reg1, $reg1, $reg2
		memory[6] = 0b00000100001000100000100000100010; // 000001 (R-Type)  00001 ($reg1)  00010 ($reg2)  00001 ($reg1) 00000 (shmat) 100010 (funct sub)

		//            V----VV---VV---VV---VV---VV----V  // addi $reg3, $reg3, 1
		memory[7] = 0b00001000011000110000000000000001; // 000010 (addi) 00011 ($reg3)  00011 ($reg3)  1 (0000000000000001)

		memory[8] = 0b00000000000000000000000000000000;
		memory[9] = 0b00000000000000000000000000000000;
		memory[10] = 0b00000000000000000000000000000000;

		//             V----VV---VV---VV---VV---VV----V  // bne $reg1, $zero, ENQUANTO
		memory[11] = 0b00011100001000000000000000000101; // 000111 (bne) 00001 ($reg1)  00000 ($zero)  0000000000000000 (offset)
		
		memory[12] = 0b00000000000000000000000000000000;
		memory[13] = 0b00000000000000000000000000000000;
		memory[14] = 0b00000000000000000000000000000000;

		memory[15] = 0b00000000000000000000000000000000; // FIM


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