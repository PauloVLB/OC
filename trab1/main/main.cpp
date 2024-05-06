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
    
    // Pc Signals
    sc_signal<sc_uint<5>> muxOutPcInSig;
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
    sc_signal<bool>        Buffer2MSig; // TODO: Mudar ta errado (bool)
    sc_signal<bool>        Buffer2EXSig; // TODO: Mudar ta errado
    sc_signal<sc_uint<32>> Buffer2NextAdressSig;
    sc_signal<sc_int<32>>  Buffer2RsDataSig;
    sc_signal<sc_int<32>>  Buffer2RtDataSig;
    sc_signal<sc_uint<32>> Buffer2RdShamtFunctExtendedSig;
    sc_signal<sc_uint<5>>  Buffer2RtSig;
    sc_signal<sc_uint<5>>  Buffer2RdSig;

    // Buffer3 Out Signals
    sc_signal<bool>        Buffer3WBSig;
    sc_signal<bool>        Buffer3MSig; // TODO: Mudar ta errado
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

    

    //========================= waveform
	sc_trace_file *fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, sc_core::SC_NS);
	//========================= 

	return 0;
}
