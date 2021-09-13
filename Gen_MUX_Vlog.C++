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
	
    FILE * vFile;
	string line;
	ifstream ini_file {"MUX_function.txt"};
	ofstream out_file {"MUX.v"};
	while(getline(ini_file,line)){
	       out_file << line << "\n";
	   }
	ini_file.close();
	out_file.close();

	
    vFile = fopen("MUX.v", "a");
    fprintf(vFile, "module w_bit_N_MUX #(parameter N = %d, m = %d, W = %d)", n, m, w);
    int i = w-1;
    string input_name ;
	string name[10];

    fprintf(vFile, " (");

    while(i >= 0 )
    {
    	//input_name = input_name + "a" + std::to_string(i) + ",";
		name[i] = "a" + std::to_string(i);
		fprintf(vFile, " %s, " ,name[i].c_str());
    	i --;
    }
    //fprintf(vFile, " ( %s " ,input_name.c_str());
	fprintf(vFile, " sel, out);\n");
	fprintf(vFile, "input [N-1:0] ");
	for(i=w-1;i>0;i--)
	{
		fprintf(vFile, "%s, " ,name[i].c_str());
	}
	fprintf(vFile, "%s ; \n" ,name[0].c_str());
	fprintf(vFile, "input [m-1:0] sel; \n");
	i = w-1;
	fprintf(vFile, "output [%d:0] out; \n", i);
	fprintf(vFile, "reg [N-1:0]matrix [0:%d] ;\n",i);
	fprintf(vFile, "genvar i; \n");
	fprintf(vFile, "always @(*) begin \n");
	for(i=w-1;i>=0;i--)
	{
		fprintf(vFile, "	matrix[%d] = %s ;\n" ,i , name[i].c_str());
	}
	fprintf(vFile, "end \n");
	fprintf(vFile, "generate \n");
	fprintf(vFile, "	for (i = 0; i < %d; i = i + 1) begin \n", w);
	fprintf(vFile, "		mux_module #(.N(%d), .m(%d)) U1 ( .inp(matrix[i]), .select(sel), .out(out[i]) ); \n", n, m);
    fprintf(vFile, "	end \n");
	fprintf(vFile, "endgenerate \n");
	fprintf(vFile, "endmodule \n");
    fclose(vFile);
	std::cout << "The verilog code is generated successfully. \n";
	cout << "The output file is in the path ~//... \n";
    return 0;

}