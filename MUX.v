//This file is created to simulate MUX...
module mux_module #(parameter N = 9, m = 4)(inp, select, out); // $floor($clog2(N))
  input [N-1:0]inp;
  input [m-1:0]select;
  output out; 
  
  wire [1:0]temp;
  wire [1:0]temp1;

  generate 
    if (N==1)
      assign out = inp[0];
    else if (N==2) begin
      assign out = (select[0]) ? inp[1] : inp[0]; 
    end
    else if (N>2) begin 
      if ((N & (N-1))==0) begin
        mux_module #(.N(N/2),.m(m-1)) M1 (.inp(inp[N/2-1:0]), .select(select[m-2:0]), .out(temp[0]) );
        mux_module #(.N(N/2),.m(m-1))  M2 (.inp(inp[N-1:N/2]), .select(select[m-2:0]), .out(temp[1]) );
        mux_module #(.N(2),.m(1)) M3 (.inp(temp), .select(select[m-1]), .out(out));
      end 
      else begin
        mux_module #(.N(2**(m-1)),.m(m-1)) M4 (.inp(inp[(2**(m-1)-1):0]), .select(select[m-2:0]), .out(temp1[0]) );
        mux_module #(.N(N - (2**(m-1))),.m(m-1)) M5 (.inp(inp[N-1:(2**(m-1))]), .select(select[m-2:0]), .out(temp1[1]) );
        mux_module #(.N(2),.m(1)) M6 (.inp(temp1), .select(select[m-1]), .out(out));
      end
    end
  endgenerate
endmodule
module w_bit_N_MUX #(parameter N = 8, m = 3, W = 8) ( a7,  a6,  a5,  a4,  a3,  a2,  a1,  a0,  sel, out);
input [N-1:0] a7, a6, a5, a4, a3, a2, a1, a0 ; 
input [m-1:0] sel; 
output [7:0] out; 
reg [N-1:0]matrix [0:7] ;
genvar i; 
always @(*) begin 
	matrix[7] = a7 ;
	matrix[6] = a6 ;
	matrix[5] = a5 ;
	matrix[4] = a4 ;
	matrix[3] = a3 ;
	matrix[2] = a2 ;
	matrix[1] = a1 ;
	matrix[0] = a0 ;
end 
generate 
	for (i = 0; i < 8; i = i + 1) begin 
		mux_module #(.N(8), .m(3)) U1 ( .inp(matrix[i]), .select(sel), .out(out[i]) ); 
	end 
endgenerate 
endmodule 
