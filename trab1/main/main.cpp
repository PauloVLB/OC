#include "systemc.h"
#include "../adder.h"
#include "../alucontrol.h"
#include "../bankregister.h"
#include "../buffer_1.h"
#include "../buffer_2.h"
#include "../buffer_3.h"
#include "../buffer_4.h"
#include "../control.h"
#include "../branch_component.h"
#include "../memory_data.h"
#include "../memory_instructions.h"
#include "../mux.h"
#include "../program_counter.h"
#include "../signal_extend.h"
#include "../ula.h"
#include "main_testbench.h"

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
    sc_signal<bool> ControlRegDstSig, ControlAluSrcSig, ControlBranchSig[2], ControlMemRdSig, ControlMemWrtSig, ControlRegWrtSig, ControlMemToRegSig;
    sc_signal<bool> ControlAluOpSig[2];

    // Buffer1 Out Signals
    // sc_signal<sc_uint<5>> Buffer1NextAdressSig;
    sc_signal<sc_uint<6>> Buffer1OpcodeSig;
    sc_signal<sc_uint<5>> Buffer1RsSig;
    sc_signal<sc_uint<5>> Buffer1RtSig;
    sc_signal<sc_uint<5>> Buffer1RdSig;
    sc_signal<sc_uint<16>> Buffer1RdShamtFunctSig;

    // Buffer2 Out Signals
    sc_signal<bool>        Buffer2WBSig[2];
    sc_signal<bool>  Buffer2MSig[4];
    sc_signal<bool>   Buffer2EXSig[4];
    // sc_signal<sc_uint<5>> Buffer2NextAdressSig;
    sc_signal<sc_int<32>>  Buffer2RsDataSig;
    sc_signal<sc_int<32>>  Buffer2RtDataSig;
    sc_signal<sc_int<32>> Buffer2RdShamtFunctExtendedSig;
    sc_signal<sc_uint<5>>  Buffer2RtSig;
    sc_signal<sc_uint<5>>  Buffer2RdSig;

    // Buffer3 Out Signals
    sc_signal<bool>        Buffer3WBSig[2];
    sc_signal<bool>  Buffer3MSig[4];
    sc_signal<sc_uint<5>>  Buffer3BranchAdressSig;
    sc_signal<bool>        Buffer3ZeroSig;
    sc_signal<sc_int<32>>  Buffer3UlaResultSig;
    sc_signal<sc_int<32>>  Buffer3RtDataSig;
    sc_signal<sc_uint<5>>  Buffer3RegDestSig;

    // Buffer4 Out Signals
    sc_signal<bool>        Buffer4WBSig[2];
    sc_signal<sc_int<32>>  Buffer4DataSig;
    sc_signal<sc_int<32>>  Buffer4UlaResultSig;
    sc_signal<sc_uint<5>>  Buffer4RegDestSig;

    // PC Adder Out Signals
    sc_signal<sc_uint<5>> PcAdderOutSig;

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

    // Branch Component Out Signals
    sc_signal<bool> BranchComponentOutSig;


    sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

    main_testbench tb("Testbench");
    tb.Clk(TestClk);

    // Modules
    pc pc("pc"); // OK!
    pc.clk(TestClk);
    pc.instruction_address_in(PcMuxOutSig);
    pc.instruction_address_out(PcAdressSig);

    imem memory_instructions("memory_instructions"); // OK!
    memory_instructions.instruction_address(PcAdressSig);
    memory_instructions.instruction_data(InstructionDataSig);

    dmem memory_data("memory_data"); // OK!
    memory_data.address(Buffer3UlaResultSig);
    memory_data.write_data(Buffer3RtDataSig);
    memory_data.mem_read(Buffer3MSig[2]);
    memory_data.mem_write(Buffer3MSig[3]);
    memory_data.read_data(MemoryDataSig);
    memory_data.clk(TestClk);

    bankreg bank_register("bank_register");
    bank_register.reg_in[0](Buffer1RsSig);
    bank_register.reg_in[1](Buffer1RtSig);
    bank_register.reg_wrt(Buffer4RegDestSig);
    bank_register.WD(MemToRegMuxOutSig);
    bank_register.WE(Buffer4WBSig[0]);
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
    alu_control.extendedSignal(Buffer2RdShamtFunctExtendedSig);
    alu_control.ALUOp[0](Buffer2EXSig[1]);
    alu_control.ALUOp[1](Buffer2EXSig[2]);
    alu_control.op(AluControlOpSig);

    control control("control");
    control.opcode(Buffer1OpcodeSig);
    control.RegDst(ControlRegDstSig);
    control.AluSrc(ControlAluSrcSig);
    control.Branch[0](ControlBranchSig[0]);
    control.Branch[1](ControlBranchSig[1]);
    control.MemRd(ControlMemRdSig);
    control.MemWrt(ControlMemWrtSig);
    control.RegWrt(ControlRegWrtSig);
    control.MemToReg(ControlMemToRegSig);
    control.AluOp[0](ControlAluOpSig[0]);
    control.AluOp[1](ControlAluOpSig[1]);
    // control.clk(TestClk);

    buffer_1 buffer1("buffer1");
    // buffer1.next_instruction_adress_in(PcAdderOutSig);
    buffer1.instruction_data_in(InstructionDataSig);
    // buffer1.next_instruction_adress_out(Buffer1NextAdressSig);
    buffer1.opcode_out(Buffer1OpcodeSig);
    buffer1.rs_out(Buffer1RsSig);
    buffer1.rt_out(Buffer1RtSig);
    buffer1.rd_out(Buffer1RdSig);
    buffer1.rdShamtFunct_out(Buffer1RdShamtFunctSig);
    buffer1.clk(TestClk);

    buffer_2 buffer2("buffer2");
    // buffer2.next_instruction_adress_in(Buffer1NextAdressSig);
    buffer2.reg_data_1_in(BankRegisterRsDataSig);
    buffer2.reg_data_2_in(BankRegisterRtDataSig);
    buffer2.instruction_1_in(SignalExtendOutSig);
    buffer2.instruction_2_in(Buffer1RtSig);
    buffer2.instruction_3_in(Buffer1RdSig);
    buffer2.WB_in[0](ControlRegWrtSig);
    buffer2.WB_in[1](ControlMemToRegSig);
    buffer2.M_in[0](ControlBranchSig[0]);
    buffer2.M_in[1](ControlBranchSig[1]);
    buffer2.M_in[2](ControlMemRdSig);
    buffer2.M_in[3](ControlMemWrtSig);
    buffer2.EX_in[0](ControlRegDstSig);
    buffer2.EX_in[1](ControlAluOpSig[0]);
    buffer2.EX_in[2](ControlAluOpSig[1]);
    buffer2.EX_in[3](ControlAluSrcSig);
    // buffer2.next_instruction_adress_out(Buffer2NextAdressSig);
    buffer2.reg_data_1_out(Buffer2RsDataSig);
    buffer2.reg_data_2_out(Buffer2RtDataSig);
    buffer2.instruction_1_out(Buffer2RdShamtFunctExtendedSig);
    buffer2.instruction_2_out(Buffer2RtSig);
    buffer2.instruction_3_out(Buffer2RdSig);
    buffer2.WB_out[0](Buffer2WBSig[0]);
    buffer2.WB_out[1](Buffer2WBSig[1]);
    buffer2.M_out[0](Buffer2MSig[0]);
    buffer2.M_out[1](Buffer2MSig[1]);
    buffer2.M_out[2](Buffer2MSig[2]);
    buffer2.M_out[3](Buffer2MSig[3]);
    buffer2.EX_out[0](Buffer2EXSig[0]);
    buffer2.EX_out[1](Buffer2EXSig[1]);
    buffer2.EX_out[2](Buffer2EXSig[2]);
    buffer2.EX_out[3](Buffer2EXSig[3]);
    buffer2.clk(TestClk);

    buffer_3 buffer3("buffer3");
    buffer3.branch_adress_in(Buffer2RdShamtFunctExtendedSig);
    buffer3.ula_zero_in(UlaZeroSig);
    buffer3.ula_result_in(UlaResultSig);
    buffer3.reg_data_2_in(Buffer2RtDataSig);
    buffer3.some_instruction_in(RegDstMuxOutSig);
    buffer3.WB_in[0](Buffer2WBSig[0]);
    buffer3.WB_in[1](Buffer2WBSig[1]);
    buffer3.M_in[0](Buffer2MSig[0]);
    buffer3.M_in[1](Buffer2MSig[1]);
    buffer3.M_in[2](Buffer2MSig[2]);
    buffer3.M_in[3](Buffer2MSig[3]);
    buffer3.branch_adress_out(Buffer3BranchAdressSig);
    buffer3.ula_zero_out(Buffer3ZeroSig);
    buffer3.ula_result_out(Buffer3UlaResultSig);
    buffer3.reg_data_2_out(Buffer3RtDataSig);
    buffer3.some_instruction_out(Buffer3RegDestSig);
    buffer3.WB_out[0](Buffer3WBSig[0]);
    buffer3.WB_out[1](Buffer3WBSig[1]);
    buffer3.M_out[0](Buffer3MSig[0]);
    buffer3.M_out[1](Buffer3MSig[1]);
    buffer3.M_out[2](Buffer3MSig[2]);
    buffer3.M_out[3](Buffer3MSig[3]);
    buffer3.clk(TestClk);

    buffer_4 buffer4("buffer4");
    buffer4.memory_data_in(MemoryDataSig);
    buffer4.ula_result_in(Buffer3UlaResultSig);
    buffer4.some_instruction_in(Buffer3RegDestSig);
    buffer4.WB_in[0](Buffer3WBSig[0]);
    buffer4.WB_in[1](Buffer3WBSig[1]);
    buffer4.memory_data_out(Buffer4DataSig);
    buffer4.ula_result_out(Buffer4UlaResultSig);
    buffer4.some_instruction_out(Buffer4RegDestSig);
    buffer4.WB_out[0](Buffer4WBSig[0]);
    buffer4.WB_out[1](Buffer4WBSig[1]);
    buffer4.clk(TestClk);

    mux5 pc_mux("pc_mux");
    pc_mux.in1(PcAdderOutSig);
    pc_mux.in2(Buffer3BranchAdressSig);
    pc_mux.choose(BranchComponentOutSig);
    pc_mux.out(PcMuxOutSig);

    mux5 reg_dst_mux("reg_dst_mux");
    reg_dst_mux.in1(Buffer2RtSig);
    reg_dst_mux.in2(Buffer2RdSig);
    reg_dst_mux.choose(Buffer2EXSig[0]);
    reg_dst_mux.out(RegDstMuxOutSig);

    mux32 alu_src_mux("alu_src_mux");
    alu_src_mux.in1(Buffer2RtDataSig);
    alu_src_mux.in2(Buffer2RdShamtFunctExtendedSig);
    alu_src_mux.choose(Buffer2EXSig[3]);
    alu_src_mux.out(AluSrcMuxOutSig);

    mux32 mem_to_reg_mux("mem_to_reg_mux");
    mem_to_reg_mux.in1(Buffer4DataSig);
    mem_to_reg_mux.in2(Buffer4UlaResultSig);
    mem_to_reg_mux.choose(Buffer4WBSig[1]);
    mem_to_reg_mux.out(MemToRegMuxOutSig);

    sign_ext signal_extend("signal_extend");
    signal_extend.in(Buffer1RdShamtFunctSig);
    signal_extend.out(SignalExtendOutSig);

    sc_signal<sc_uint<5>> one_signal;
    one_signal.write(1);
    adder5 pc_adder("pc_adder"); // TODO: Cometi ilegalidades?
    pc_adder.in1(PcAdressSig);
    pc_adder.in2(one_signal);
    pc_adder.out(PcAdderOutSig);

    branch_component branch_component("branch_component");
    branch_component.Branch[0](Buffer3MSig[0]);
    branch_component.Branch[1](Buffer3MSig[1]);
    branch_component.zero(Buffer3ZeroSig);
    branch_component.PCSrc(BranchComponentOutSig);
    

    //========================= waveform
	sc_trace_file *fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, sc_core::SC_NS);
    sc_trace(fp, TestClk, "TestClk");
    sc_trace(fp, PcAdressSig, "PcAdressSig");
    sc_trace(fp, InstructionDataSig, "InstructionDataSig");
    sc_trace(fp, MemoryDataSig, "MemoryDataSig");
    sc_trace(fp, BankRegisterRsDataSig, "BankRegisterRsDataSig");
    sc_trace(fp, BankRegisterRtDataSig, "BankRegisterRtDataSig");
    sc_trace(fp, UlaZeroSig, "UlaZeroSig");
    sc_trace(fp, UlaResultSig, "UlaResultSig");
    sc_trace(fp, AluControlOpSig, "AluControlOpSig");
    sc_trace(fp, ControlRegDstSig, "ControlRegDstSig");
    sc_trace(fp, ControlAluSrcSig, "ControlAluSrcSig");
    sc_trace(fp, ControlBranchSig[0], "ControlBranchSig_0");
    sc_trace(fp, ControlBranchSig[1], "ControlBranchSig_1");
    sc_trace(fp, ControlMemRdSig, "ControlMemRdSig");
    sc_trace(fp, ControlMemWrtSig, "ControlMemWrtSig");
    sc_trace(fp, ControlRegWrtSig, "ControlRegWrtSig");
    sc_trace(fp, ControlMemToRegSig, "ControlMemToRegSig");
    sc_trace(fp, ControlAluOpSig[0], "ControlAluOpSig_0");
    sc_trace(fp, ControlAluOpSig[1], "ControlAluOpSig_1");
    sc_trace(fp, Buffer1OpcodeSig, "Buffer1OpcodeSig");
    sc_trace(fp, Buffer1RsSig, "Buffer1RsSig");
    sc_trace(fp, Buffer1RtSig, "Buffer1RtSig");
    sc_trace(fp, Buffer1RdSig, "Buffer1RdSig");
    sc_trace(fp, Buffer1RdShamtFunctSig, "Buffer1RdShamtFunctSig");
    sc_trace(fp, Buffer2WBSig[0], "Buffer2WBSig_0");
    sc_trace(fp, Buffer2WBSig[1], "Buffer2WBSig_1");
    sc_trace(fp, Buffer2MSig[0], "Buffer2MSig_0");
    sc_trace(fp, Buffer2MSig[1], "Buffer2MSig_1");
    sc_trace(fp, Buffer2MSig[2], "Buffer2MSig_2");
    sc_trace(fp, Buffer2MSig[3], "Buffer2MSig_3");
    sc_trace(fp, Buffer2EXSig[0], "Buffer2EXSig_0");
    sc_trace(fp, Buffer2EXSig[1], "Buffer2EXSig_1");
    sc_trace(fp, Buffer2EXSig[2], "Buffer2EXSig_2");
    sc_trace(fp, Buffer2EXSig[3], "Buffer2EXSig_3");
    sc_trace(fp, Buffer2RsDataSig, "Buffer2RsDataSig");
    sc_trace(fp, Buffer2RtDataSig, "Buffer2RtDataSig");
    sc_trace(fp, Buffer2RdShamtFunctExtendedSig, "Buffer2RdShamtFunctExtendedSig");
    sc_trace(fp, Buffer2RtSig, "Buffer2RtSig");
    sc_trace(fp, Buffer2RdSig, "Buffer2RdSig");
    sc_trace(fp, Buffer3WBSig[0], "Buffer3WBSig_0");
    sc_trace(fp, Buffer3WBSig[1], "Buffer3WBSig_1");
    sc_trace(fp, Buffer3MSig[0], "Buffer3MSig_0");
    sc_trace(fp, Buffer3MSig[1], "Buffer3MSig_1");
    sc_trace(fp, Buffer3MSig[2], "Buffer3MSig_2");
    sc_trace(fp, Buffer3MSig[3], "Buffer3MSig_3");
    sc_trace(fp, Buffer3BranchAdressSig, "Buffer3BranchAdressSig");
    sc_trace(fp, Buffer3ZeroSig, "Buffer3ZeroSig");
    sc_trace(fp, Buffer3UlaResultSig, "Buffer3UlaResultSig");
    sc_trace(fp, Buffer3RtDataSig, "Buffer3RtDataSig");
    sc_trace(fp, Buffer3RegDestSig, "Buffer3RegDestSig");
    sc_trace(fp, Buffer4WBSig[0], "Buffer4WBSig_0");
    sc_trace(fp, Buffer4WBSig[1], "Buffer4WBSig_1");
    sc_trace(fp, Buffer4DataSig, "Buffer4DataSig");
    sc_trace(fp, Buffer4UlaResultSig, "Buffer4UlaResultSig");
    sc_trace(fp, Buffer4RegDestSig, "Buffer4RegDestSig");
    sc_trace(fp, PcAdderOutSig, "PcAdderOutSig");
    sc_trace(fp, SignalExtendOutSig, "SignalExtendOutSig");
    sc_trace(fp, PcMuxOutSig, "PcMuxOutSig");
    sc_trace(fp, RegDstMuxOutSig, "RegDstMuxOutSig");
    sc_trace(fp, AluSrcMuxOutSig, "AluSrcMuxOutSig");
    sc_trace(fp, MemToRegMuxOutSig, "MemToRegMuxOutSig");
    sc_trace(fp, BranchComponentOutSig, "BranchComponentOutSig");

	//========================= 

    sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
