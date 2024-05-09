#include "systemc.h"
#include "buffer1_testbench.h"
#include "../../buffer_1.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<32>> instruction_data_in_sig;
	sc_signal<sc_uint<6>> opcode_out_sig;
	sc_signal<sc_uint<5>> rs_out_sig;
	sc_signal<sc_uint<5>> rt_out_sig;
	sc_signal<sc_uint<5>> rd_out_sig;
	sc_signal<sc_uint<16>> rdShamtFunct_out_sig;


	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	buffer1_testbench Tb("Testbench");
	Tb.instruction_data_in(instruction_data_in_sig);
	Tb.Clk(TestClk);

	buffer_1 b1("buffer1");
	b1.instruction_data_in(instruction_data_in_sig);
	b1.opcode_out(opcode_out_sig);
	b1.rs_out(rs_out_sig);
	b1.rt_out(rt_out_sig);
	b1.rd_out(rd_out_sig);
	b1.rdShamtFunct_out(rdShamtFunct_out_sig);
    b1.clk(TestClk);

	//========================= waveform
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, sc_core::SC_NS);
	sc_trace(fp, TestClk, "Clock");
	sc_trace(fp, instruction_data_in_sig, "data_in");
	sc_trace(fp, opcode_out_sig, "opcode_out");
	sc_trace(fp, rs_out_sig, "rs_out");
	sc_trace(fp, rt_out_sig, "rt_out");
	sc_trace(fp, rd_out_sig, "rd_out");
	sc_trace(fp, rdShamtFunct_out_sig, "rdShamtFunct_out");
	//========================= 

	sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
