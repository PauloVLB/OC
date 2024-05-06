#include "systemc.h"
#include "buffer1_testbench.h"
#include "../../buffer_1.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<32>> next_instruction_adress_in_sig;
    sc_signal<sc_uint<32>> instruction_data_in_sig;

    sc_signal<sc_uint<32>> next_instruction_adress_out_sig; // Maybe change this size
    sc_signal<sc_uint<32>> instruction_data_out_sig;

	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	buffer1_testbench Tb("Testbench");
	Tb.next_instruction_adress_in(next_instruction_adress_in_sig);
	Tb.instruction_data_in(instruction_data_in_sig);
	Tb.Clk(TestClk);

	buffer_1 b1("buffer1");
	b1.next_instruction_adress_in(next_instruction_adress_in_sig);
	b1.instruction_data_in(instruction_data_in_sig);
	b1.next_instruction_adress_out(next_instruction_adress_out_sig);
	b1.instruction_data_out(instruction_data_out_sig);
    b1.clk(TestClk);

	//========================= waveform
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, sc_core::SC_NS);
	sc_trace(fp, TestClk, "Clock");
	sc_trace(fp, next_instruction_adress_in_sig, "adress_in");
	sc_trace(fp, instruction_data_in_sig, "data_in");
	sc_trace(fp, next_instruction_adress_out_sig, "adress_out");
	sc_trace(fp, instruction_data_out_sig, "data_out");
	//========================= 

	sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
