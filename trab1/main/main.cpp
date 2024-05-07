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
    sc_signal<sc_uint<3>>  AluControlOpSig;

    // Control Out Signals
    sc_out<bool> ControlRegDstSig, ControlAluSrcSig, ControlBranchSig, ControlMemRdSig, ControlMemWrtSig, ControlRegWrtSig, ControlMemToRegSig;
    sc_signal<sc_uint<2>> ControlAluOpSig;

    // Buffer1 Out Signals
    sc_signal<sc_uint<32>> Buffer1InstructionDataSig;
    sc_signal<sc_uint<5>> Buffer1NextAdressSig;

    // Buffer2 Out Signals
    sc_signal<bool>        Buffer2WBSig; // TODO: TA ERRADO
    sc_signal<sc_uint<3>>  Buffer2MSig;
    sc_signal<sc_uint<4>>   Buffer2EXSig;
    sc_signal<sc_uint<5>> Buffer2NextAdressSig;
    sc_signal<sc_int<32>>  Buffer2RsDataSig;
    sc_signal<sc_int<32>>  Buffer2RtDataSig;
    sc_signal<sc_int<32>> Buffer2RdShamtFunctExtendedSig;
    sc_signal<sc_uint<5>>  Buffer2RtSig;
    sc_signal<sc_uint<5>>  Buffer2RdSig;

    // Buffer3 Out Signals
    sc_signal<bool>        Buffer3WBSig; // TODO: TA ERRADO
    sc_signal<sc_uint<3>>  Buffer3MSig;
    sc_signal<sc_uint<5>>  Buffer3AddResultSig;
    sc_signal<bool>        Buffer3ZeroSig;
    sc_signal<sc_int<32>>  Buffer3UlaResultSig;
    sc_signal<sc_int<32>>  Buffer3RtDataSig;
    sc_signal<sc_uint<5>>  Buffer3RegDestSig;

    // Buffer4 Out Signals
    sc_signal<bool>        Buffer4WBSig; // TODO: TA ERRADO
    sc_signal<sc_int<32>>  Buffer4DataSig;
    sc_signal<sc_int<32>>  Buffer4UlaResultSig;
    sc_signal<sc_uint<5>>  Buffer4RegDestSig;

    // PC Adder Out Signals
    sc_signal<sc_uint<5>> PcAdderOutSig;

    // Branch Adder Out Signals
    sc_signal<sc_uint<5>> BranchAdderOutSig;

    // Signal Extend Out Signals
    sc_signal<sc_int<32>> SignalExtendOutSig;

    // PC Mux Out Signals
    sc_signal<sc_uint<5>> PcMuxOutSig;

    // RegDst Mux Out Signals
    sc_signal<sc_uint<5>> RegDstMuxOutSig;

    // AluSrc Mux Out Signals
    sc_signal<sc_int<32>> AluSrcMuxOutSig;

    // MemToReg Mux Out Signals
    sc_signal<sc_int<32>> MemToRegMuxOutSig;

    // Instruction Decoder Out Signals
    sc_signal<sc_uint<6>> InstructionDecoderOpcodeSig;
    sc_signal<sc_uint<6>> InstructionDecoderRsSig;
    sc_signal<sc_uint<6>> InstructionDecoderRtSig;
    sc_signal<sc_uint<6>> InstructionDecoderRdSig;
    sc_signal<sc_uint<6>> InstructionDecoderRdShamtFunctSig;



    sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

    
    // Modules
    pc pc("pc"); // OK!
    pc.clk(TestClk);
    pc.instruction_address_in(PcMuxOutSig);
    pc.instruction_address_out(PcAdressSig);

    imem memory_instructions("memory_instructions"); // OK!
    memory_instructions.instruction_address(PcAdressSig);
    memory_instructions.instruction_data(InstructionDataSig);

    dmem memory_data("memory_data");
    memory_data.address(Buffer3UlaResultSig);
    memory_data.write_data(Buffer3RtDataSig);
    // memory_data.mem_read(Buffer3MSig[1]); CHANGE ME
    // memory_data.mem_write(Buffer3MSig[2]); CHANGE ME
    memory_data.read_data(MemoryDataSig);
    memory_data.clk(TestClk);

    bankreg bank_register("bank_register");
    // bank_register.reg_in[0](); CHANGE ME
    // bank_register.reg_in[1](); CHANGE ME
    bank_register.reg_wrt(Buffer4RegDestSig);
    bank_register.WD(MemToRegMuxOutSig);
    // bank_register.WE(Buffer4WBSig); // TODO: TA ERRADO
    bank_register.reg_out[0](BankRegisterRsDataSig);
    bank_register.reg_out[1](BankRegisterRtDataSig);
    bank_register.clk(TestClk);

    ula ula("ula"); // OK!
    ula.A(Buffer2RsDataSig);
    ula.B(AluSrcMuxOutSig);
    ula.op(AluControlOpSig);
    ula.zero(UlaZeroSig);
    ula.result(UlaResultSig);

    alucontrol alu_control("alu_control");
    // alu_control.function_code(); CHANGE ME
    // alu_control.ALUOp(); CHANGE ME
    alu_control.op(AluControlOpSig);

    control control("control");
    // control.opcode(); CHANGE ME
    control.RegDst(ControlRegDstSig);
    control.AluSrc(ControlAluSrcSig);
    control.Branch(ControlBranchSig);
    control.MemRd(ControlMemRdSig);
    control.MemWrt(ControlMemWrtSig);
    control.RegWrt(ControlRegWrtSig);
    control.MemToReg(ControlMemToRegSig);
    control.AluOp(ControlAluOpSig);
    control.clk(TestClk);

    buffer_1 buffer1("buffer1");
    buffer1.next_instruction_adress_in(PcAdderOutSig);
    buffer1.instruction_data_in(InstructionDataSig);
    buffer1.next_instruction_adress_out(Buffer1NextAdressSig);
    // buffer1.instruction_data_out(Buffer1InstructionDataSig); MAYBE CHANGE ME
    buffer1.clk(TestClk);

    buffer_2 buffer2("buffer2");
    buffer2.next_instruction_adress_in(Buffer1NextAdressSig);
    buffer2.reg_data_1_in(BankRegisterRsDataSig);
    buffer2.reg_data_2_in(BankRegisterRtDataSig);
    buffer2.instruction_1_in(SignalExtendOutSig);
    // buffer2.instruction_2_in(); CHANGE ME
    // buffer2.instruction_3_in(); CHANGE ME
    // buffer2.WB_in(ControlRegWrtSig); // TODO: TA ERRADO
    // buffer2.M_in(); // CHANGE ME
    // buffer2.EX_in(); // CHANGE ME
    buffer2.next_instruction_adress_out(Buffer2NextAdressSig);
    buffer2.reg_data_1_out(Buffer2RsDataSig);
    buffer2.reg_data_2_out(Buffer2RtDataSig);
    // buffer2.instruction_1_out(); MAYBE CHANGE ME
    buffer2.instruction_2_out(Buffer2RtSig);
    buffer2.instruction_3_out(Buffer2RdSig);
    // buffer2.WB_out(Buffer2WBSig); // TODO: TA ERRADO
    // buffer2.M_out(); // CHANGE ME
    // buffer2.EX_out(); // CHANGE ME
    buffer2.clk(TestClk);

    buffer_3 buffer3("buffer3");
    buffer3.add_result_in(BranchAdderOutSig);
    buffer3.ula_zero_in(UlaZeroSig);
    buffer3.ula_result_in(UlaResultSig);
    buffer3.reg_data_2_in(Buffer2RtDataSig);
    buffer3.some_instruction_in(RegDstMuxOutSig);
    // buffer3.WB_in(Buffer2WBSig); // TODO: TA ERRADO
    // buffer3.M_in(); CHANGE ME
    buffer3.add_result_out(Buffer3AddResultSig);
    buffer3.ula_zero_out(Buffer3ZeroSig);
    buffer3.ula_result_out(Buffer3UlaResultSig);
    buffer3.reg_data_2_out(Buffer3RtDataSig);
    buffer3.some_instruction_out(Buffer3RegDestSig);
    // buffer3.WB_out(Buffer3WBSig); // TODO: TA ERRADO
    // buffer3.M_out(); CHANGE ME
    buffer3.clk(TestClk);

    buffer_4 buffer4("buffer4");
    buffer4.memory_data_in(MemoryDataSig);
    buffer4.ula_result_in(Buffer3UlaResultSig);
    buffer4.some_instruction_in(Buffer3RegDestSig);
    // buffer4.WB_in(Buffer3WBSig); // TODO: TA ERRADO
    buffer4.memory_data_out(Buffer4DataSig);
    buffer4.ula_result_out(Buffer4UlaResultSig);
    buffer4.some_instruction_out(Buffer4RegDestSig);
    // buffer4.WB_out(Buffer4WBSig); // TODO: TA ERRADO
    buffer4.clk(TestClk);

    mux5 pc_mux("pc_mux");
    pc_mux.in1(PcAdderOutSig);
    pc_mux.in2(Buffer3AddResultSig);
    // pc_mux.choose(); CHANGE ME
    pc_mux.out(PcMuxOutSig);

    mux5 reg_dst_mux("reg_dst_mux");
    reg_dst_mux.in1(Buffer2RtSig);
    reg_dst_mux.in2(Buffer2RdSig);
    // reg_dst_mux.choose(); CHANGE ME
    reg_dst_mux.out(RegDstMuxOutSig);

    mux32 alu_src_mux("alu_src_mux");
    alu_src_mux.in1(Buffer2RtDataSig);
    alu_src_mux.in2(Buffer2RdShamtFunctExtendedSig);
    // alu_src_mux.choose(); CHANGE ME
    alu_src_mux.out(AluSrcMuxOutSig);

    mux32 mem_to_reg_mux("mem_to_reg_mux");
    mem_to_reg_mux.in1(Buffer4DataSig);
    mem_to_reg_mux.in2(Buffer4UlaResultSig);
    // mem_to_reg_mux.choose(); CHANGE ME
    mem_to_reg_mux.out(MemToRegMuxOutSig);

    sign_ext signal_extend("signal_extend");
    // signal_extend.in(); CHANGE ME
    signal_extend.out(SignalExtendOutSig); // TODO: VER SE DA CERTO ISSO AI TA LIGADO

    sc_signal<sc_uint<5>> one_signal;
    one_signal.write(1);
    adder5 pc_adder("pc_adder"); // TODO: Cometi ilegalidades?
    pc_adder.in1(PcAdressSig);
    pc_adder.in2(one_signal);
    pc_adder.out(PcAdderOutSig);

    adder5 branch_adder("branch_adder");
    branch_adder.in1(Buffer2NextAdressSig);
    // branch_adder.in2(); CHANGE ME???????????????????????????
    branch_adder.out(BranchAdderOutSig);

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
