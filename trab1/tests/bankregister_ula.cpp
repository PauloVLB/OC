#include "systemc.h"
#include "bankregister_ula_testbench.h"
#include "../ula.h"
#include "../bankregister.h"

int sc_main(int argc, char* argv[]) {
    
	sc_signal<sc_int<32>> out_bank_reg_in_a, out_bank_reg_in_b;

	sc_signal<sc_uint<3>> opSig;
	sc_signal<bool> zeroSig;
    sc_signal<sc_int<32>> resultSig;

    sc_signal<sc_uint<5>> reg_inSig[2];
    sc_signal<sc_uint<5>> reg_wrtSig;   
    sc_signal<sc_int<32>> WDSig;
    sc_signal<bool> WESig;

	sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

	bankregister_ula_testbench Tb("Testbench");
	Tb.reg_in[0](reg_inSig[0]);
	Tb.reg_in[1](reg_inSig[1]);	
	Tb.reg_wrt(reg_wrtSig);
	Tb.WD(WDSig);
	Tb.WE(WESig);
	Tb.op(opSig);
	Tb.Clk(TestClk);

	ula ULA("ula");
	ULA.A(out_bank_reg_in_a);
	ULA.B(out_bank_reg_in_b);
	ULA.op(opSig);
	ULA.zero(zeroSig);
	ULA.result(resultSig);

	bankreg BANCO("bankregistrador");
	BANCO.reg_in[0](reg_inSig[0]);
	BANCO.reg_in[1](reg_inSig[1]);
    BANCO.reg_wrt(reg_wrtSig);   
    BANCO.WD(WDSig);
    BANCO.reg_out[0](out_bank_reg_in_a);
	BANCO.reg_out[1](out_bank_reg_in_b);
	BANCO.WE(WESig);
	BANCO.clk(TestClk);

	//========================= waveform
	sc_trace_file *fp;
	fp=sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, sc_core::SC_NS);
	sc_trace(fp, TestClk, "Clock");
	sc_trace(fp, reg_inSig[0], "reg_in0");
	sc_trace(fp, reg_inSig[1], "reg_in1");
	sc_trace(fp, reg_wrtSig, "reg_wrt");
	sc_trace(fp, WDSig, "WD");
	sc_trace(fp, WESig, "WE");
	sc_trace(fp, out_bank_reg_in_a, "out_bank_reg_in_a");
	sc_trace(fp, out_bank_reg_in_b, "out_bank_reg_in_b");
	sc_trace(fp, opSig, "op");
	sc_trace(fp, zeroSig, "zero");
	sc_trace(fp, resultSig, "result");
	//========================= 

	sc_start();

	sc_close_vcd_trace_file(fp);

	return 0;
}
