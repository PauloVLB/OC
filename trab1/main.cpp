#include "systemc.h"
#include "testbench.h"
#include "ula.h"

int sc_main(int argc, char* argv[]) {
    
	sc_signal<sc_int<32>> ASig, BSig;
	sc_signal<sc_uint<3>> opSig;
	sc_signal<bool> zeroSig;
    sc_signal<sc_int<32>> resultSig;

	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	testbench Tb("Testbench");
	Tb.A(ASig);
	Tb.B(BSig);
	Tb.op(opSig);
	Tb.Clk(TestClk);

	ula ULA("ula");
	ULA.A(ASig);
	ULA.B(BSig);
	ULA.op(opSig);
	ULA.zero(zeroSig);
	ULA.result(resultSig);

	//========================= waveform
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, sc_core::SC_NS);
	sc_trace(fp,ULA.A,"A");
	sc_trace(fp,ULA.B,"B");
	sc_trace(fp,ULA.op,"op");
	sc_trace(fp,ULA.zero,"zero");
	sc_trace(fp,ULA.result,"result");
	sc_trace(fp,TestClk,"CLK");
	//========================= 

	sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
