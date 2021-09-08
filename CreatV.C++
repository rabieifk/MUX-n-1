#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    int N, W, m;
    /*cout << "N = ";
    cin >> N;
    m = ceil(log2(N));
    cout << "N = " << N << "\n";
    cout << "m = " << m << "\n";
    cout << "W = ";
    cin >> W;
    cout << "W = " << W;
*/
    N = 4;
    W = 4;
    m = 2;
    int i = W-1;
    string name[10];
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
    fprintf(vFile, "module w_bit_N_MUX #(parameter N = %d, m = %d, W = %d)", N, m, W);
    fprintf(vFile, " (");
    while(i >= 0 )
    {
	name[i] = "a" + std::to_string(i);
	fprintf(vFile, " %s, " ,name[i].c_str());
    	i --;
    }
    fprintf(vFile, " sel, out);\n");
    fprintf(vFile, "input [N-1:0] ");
    for(i=W-1;i>0;i--){
	fprintf(vFile, "%s, " ,name[i].c_str());
    }
    fprintf(vFile, "%s ; \n" ,name[0].c_str());
    fprintf(vFile, "input [m-1:0] sel; \n");
    i = W-1;
    fprintf(vFile, "output [%d:0] out; \n", i);
    fprintf(vFile, "reg [N-1:0]matrix [0:%d] ;\n",i);
    fprintf(vFile, "genvar i; \n");
    fprintf(vFile, "always @(*) begin \n");
    for(i=W-1;i>=0;i--){
	fprintf(vFile, "	matrix[%d] = %s ;\n" ,i , name[i].c_str());
    }
    fprintf(vFile, "end \n");
    fprintf(vFile, "generate \n");
    fprintf(vFile, "	for (i = 0; i < %d; i = i + 1) begin \n", W);
    fprintf(vFile, "		mux_module #(.N(%d), .m(%d)) U1 ( .inp(matrix[i]), .select(sel), .out(out[i]) ); \n", N, m);
    fprintf(vFile, "	end \n");
    fprintf(vFile, "endgenerate \n");
    fprintf(vFile, "endmodule \n");
    fclose(vFile);
    return 0;

}
