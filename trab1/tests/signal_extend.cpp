#include "systemc.h"
#include "signal_extend_testbench.h"
#include "../signal_extend.h"

int sc_main(int argc, char* argv[]) {

    sc_signal<sc_uint<16>> in_sig;
    sc_signal<sc_int<32>> out_sig;

	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	signal_extend_testbench Tb("Testbench");
	Tb.in(in_sig);
	Tb.Clk(TestClk);

	sign_ext sig_ex("signal_extend");
	sig_ex.in(in_sig);
	sig_ex.out(out_sig);

	//========================= waveform
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, sc_core::SC_NS);
	sc_trace(fp, TestClk, "Clock");
	sc_trace(fp, in_sig, "in");
	sc_trace(fp, out_sig, "out");
	//========================= 

	sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
