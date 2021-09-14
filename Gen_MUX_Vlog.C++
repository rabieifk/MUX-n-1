#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "lib/ArgScanner.hpp"


using namespace std;

void PrintHelp()
{
	printf("\n-h:***help");
	printf("\n-Gen_MUX_Vlog--To Generate a Vrilog code implementing a N-to-1 Multiplexer, each input has the width of W-bit. ");
	printf("\n-Gen_MUX_Vlog -n N -w W");
	printf("\n-for example: Gen_MUX_Vlog -n 6 -w 4: 4-bit input width 6-to-1 MUX \n");
}

int main(int argc, const char ** argv)
{
	ArgReader args(argv, argc);

    	if(argc<=1)
        	printf("\nNo Extra Command Line Argument Passed.");
	if (args.IsSet("-h"))
		PrintHelp();
	int w = args.GetValInt("-w");
	int n = args.GetValInt("-n");

	cout << "\nGeneratig Verilog Code For Multiplex with arbitary input numbers and input width... \n";
	cout << "\n***" << n <<"-to-1 MUX with " << w << "-bit input width*** \n";	
	int m = ceil(log2(n));
	
	string line;
	ifstream ini_file {"MUX_function.txt"};
	ofstream out_file {"MUX.v"};
	while(getline(ini_file,line)){
	       out_file << line << "\n";
	   }
	ini_file.close();
	out_file.close();

	FILE * verilog_file;
    	verilog_file = fopen("MUX.v", "a");
    	fprintf(verilog_file, "module w_bit_N_MUX #(parameter N = %d, m = %d, W = %d)", n, m, w);
	string *input_port_name = NULL;
	input_port_name = new string[w];
    	fprintf(verilog_file, " (");
	int i = w-1;
    	while(i >= 0 ){
		input_port_name[i] = "a" + std::to_string(i);
		fprintf(verilog_file, " %s, " ,input_port_name[i].c_str());
    		i --;
    	}
	fprintf(verilog_file, " sel, out);\n");
	fprintf(verilog_file, "input [N-1:0] ");
	for(i=w-1;i>0;i--){
		fprintf(verilog_file, "%s, " ,input_port_name[i].c_str());
	}
	fprintf(verilog_file, "%s ; \n" ,input_port_name[0].c_str());
	fprintf(verilog_file, "input [m-1:0] sel; \n");
	i = w-1;
	fprintf(verilog_file, "output [%d:0] out; \n", i);
	fprintf(verilog_file, "reg [N-1:0]matrix [0:%d] ;\n",i);
	fprintf(verilog_file, "genvar i; \n");
	fprintf(verilog_file, "always @(*) begin \n");
	for(i=w-1;i>=0;i--){
		fprintf(verilog_file, "	matrix[%d] = %s ;\n" ,i , input_port_name[i].c_str());
	}
	fprintf(verilog_file, "end \n");
	fprintf(verilog_file, "generate \n");
	fprintf(verilog_file, "	for (i = 0; i < %d; i = i + 1) begin \n", w);
	fprintf(verilog_file, "		mux_module #(.N(%d), .m(%d)) U1 ( .inp(matrix[i]), .select(sel), .out(out[i]) ); \n", n, m);
    	fprintf(verilog_file, "	end \n");
	fprintf(verilog_file, "endgenerate \n");
	fprintf(verilog_file, "endmodule \n");
    	fclose(verilog_file);
	std::cout << "The verilog code is generated successfully. \n";
	cout << "The output file is in the path ~//... \n";
	delete [] input_port_name ;
    	return 0;

}
