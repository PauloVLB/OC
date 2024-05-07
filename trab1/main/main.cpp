#include "systemc.h"
#include "../adder.h"
#include "../alucontrol.h"
#include "../bankregister.h"
#include "../buffer_1.h"
#include "../buffer_2.h"
#include "../buffer_3.h"
#include "../buffer_4.h"
#include "../control.h"
#include "../instruction_decoder.h"
#include "../memory_data.h"
#include "../memory_instructions.h"
#include "../mux.h"
#include "../program_counter.h"
#include "../signal_extend.h"
#include "../ula.h"

int sc_main(int argc, char* argv[]) {
    
    // Pc Out Signals
    sc_signal<sc_uint<5>> PcAdressSig;

    // Instruction Memory Out Signals
    sc_signal<sc_uint<32>> InstructionDataSig;

    // Data Memory Out Signals
    sc_signal<sc_int<32>>  MemoryDataSig;

    // BankRegister Out Signals
    sc_signal<sc_int<32>>  BankRegisterRsDataSig;
    sc_signal<sc_int<32>>  BankRegisterRtDataSig;

    // Ula Out Signals
    sc_signal<bool>        UlaZeroSig;
    sc_signal<sc_int<32>>  UlaResultSig;

    // AluControl Out Signals
    sc_signal<sc_uint<4>>  AluControlOpSig;

    // Control Out Signals
    sc_out<bool> ControlRegDstSig, ControlAluSrcSig, ControlBranchSig, ControlMemRdSig, ControlMemWrtSig, ControlRegWrtSig, ControlMemToRegSig;
    sc_uint<2> ControlAluOpSig;

    // Buffer1 Out Signals
    sc_signal<sc_uint<32>> Buffer1InstructionDataSig;
    sc_signal<sc_uint<32>> Buffer1NextAdressSig;

    // Buffer2 Out Signals
    sc_signal<bool>        Buffer2WBSig; 
    sc_signal<sc_uint<3>>  Buffer2MSig;
    sc_signal<sc_uint<4>>   Buffer2EXSig;
    sc_signal<sc_uint<32>> Buffer2NextAdressSig;
    sc_signal<sc_int<32>>  Buffer2RsDataSig;
    sc_signal<sc_int<32>>  Buffer2RtDataSig;
    sc_signal<sc_uint<32>> Buffer2RdShamtFunctExtendedSig;
    sc_signal<sc_uint<5>>  Buffer2RtSig;
    sc_signal<sc_uint<5>>  Buffer2RdSig;

    // Buffer3 Out Signals
    sc_signal<bool>        Buffer3WBSig;
    sc_signal<sc_uint<3>>  Buffer3MSig;
    sc_signal<sc_uint<5>>  Buffer3AddResultSig;
    sc_signal<bool>        Buffer3ZeroSig;
    sc_signal<sc_int<32>>  Buffer3UlaResultSig;
    sc_signal<sc_uint<32>> Buffer3RtDataSig;
    sc_signal<sc_uint<5>>  Buffer3RegDestSig;

    // Buffer4 Out Signals
    sc_signal<bool>        Buffer4WBSig;
    sc_signal<sc_int<32>>  Buffer4DataSig;
    sc_signal<sc_int<32>>  Buffer4UlaResultSig;
    sc_signal<sc_uint<5>>  Buffer4RegDestSig;

    // Instruction Decoder Out Signals
    sc_signal<sc_uint<6>> InstructionDecoderOpcodeSig;
    sc_signal<sc_uint<6>> InstructionDecoderRsSig;
    sc_signal<sc_uint<6>> InstructionDecoderRtSig;
    sc_signal<sc_uint<6>> InstructionDecoderRdSig;
    sc_signal<sc_uint<6>> InstructionDecoderRdShamtFunctSig;



    sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

    
    // Modules
    pc pc("pc");
    pc.clk(TestClk);
    // pc.instruction_address_in(PcAdressSig);  CHANGE ME
    pc.instruction_address_out(PcAdressSig);

    imem memory_instructions("memory_instructions");
    memory_instructions.instruction_address(PcAdressSig);
    memory_instructions.instruction_data(InstructionDataSig);

    dmem memory_data("memory_data");
    // memory_data.address();
    // memory_data.write_data();
    // memory_data.mem_read();
    // memory_data.mem_write();
    // memory_data.read_data();
    // memory_data.clk(TestClk);

    bankreg bank_register("bank_register");
    // bank_register.reg_in[0]();
    // bank_register.reg_in[1]();
    // bank_register.reg_wrt();
    // bank_register.WD();
    // bank_register.WE();
    // bank_register.reg_out[0]();
    // bank_register.reg_out[1]();
    bank_register.clk(TestClk);

    ula ula("ula");
    // ula.A();
    // ula.B();
    // ula.op();
    // ula.zero();
    // ula.result();

    alucontrol alu_control("alu_control");
    // alu_control.function_code();
    // alu_control.ALUOp();
    // alu_control.op();

    control control("control");
    // control.opcode();
    // control.RegDst();
    // control.AluSrc();
    // control.Branch();
    // control.MemRd();
    // control.MemWrt();
    // control.RegWrt();
    // control.MemToReg();
    // control.ALUOp();
    // control.clk(TestClk);

    buffer_1 buffer1("buffer1");
    // buffer1.next_instruction_adress_in();
    // buffer1.instruction_data_in();
    // buffer1.next_instruction_adress_out();
    // buffer1.instruction_data_out();
    // buffer1.clk(TestClk);

    buffer_2 buffer2("buffer2");
    // buffer2.next_instruction_adress_in();
    // buffer2.reg_data_1_in();
    // buffer2.reg_data_2_in();
    // buffer2.instruction_1_in();
    // buffer2.instruction_2_in();
    // buffer2.instruction_3_in();
    // buffer2.WB_in();
    // buffer2.M_in();
    // buffer2.EX_in();
    // buffer2.next_instruction_adress_out();
    // buffer2.reg_data_1_out();
    // buffer2.reg_data_2_out();
    // buffer2.instruction_1_out();
    // buffer2.instruction_2_out();
    // buffer2.instruction_3_out();
    // buffer2.WB_out();
    // buffer2.M_out();
    // buffer2.EX_out();
    // buffer2.clk(TestClk);

    buffer_3 buffer3("buffer3");
    // buffer3.add_result_in();
    // buffer3.ula_zero_in();
    // buffer3.ula_result_in();
    // buffer3.reg_data_2_in();
    // buffer3.some_instruction_in();
    // buffer3.WB_in();
    // buffer3.M_in();
    // buffer3.add_result_out();
    // buffer3.ula_zero_out();
    // buffer3.ula_result_out();
    // buffer3.reg_data_2_out();
    // buffer3.some_instruction_out();
    // buffer3.WB_out();
    // buffer3.M_out();
    // buffer3.clk(TestClk);

    buffer_4 buffer4("buffer4");
    // buffer4.memory_data_in();
    // buffer4.ula_result_in();
    // buffer4.some_instruction_in();
    // buffer4.WB_in();
    // buffer4.memory_data_out();
    // buffer4.ula_result_out();
    // buffer4.some_instruction_out();
    // buffer4.WB_out();
    // buffer4.clk(TestClk);

    instruction_decoder instruction_decoder("instruction_decoder");
    // instruction_decoder.instr();
    // instruction_decoder.opcode();
    // instruction_decoder.rs();
    // instruction_decoder.rt();
    // instruction_decoder.rd();
    // instruction_decoder.rd_shamt_funct();
    

    //========================= waveform
	sc_trace_file *fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, sc_core::SC_NS);
	//========================= 

	return 0;
}
