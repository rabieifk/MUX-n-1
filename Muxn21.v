

module mux_module #(parameter N = 8, m = $clog2(N))(inp, select, out);
  input [N-1:0]inp;
  input [m-1:0]select;
  output out; 
  
  wire [1:0]temp;
  generate
    if (N==2) begin
      assign out = (select[0]) ? inp[1] : inp[0]; 
    end
    else begin
      mux_module #(.N(N/2),.m(m-1)) M1 (.inp(inp[N/2:0]), .select(select[m-2:0]), .out(temp[0]) );
      mux_module #(.N(N/2),.m(m-1)) M2 (.inp(inp[N-1:N/2]), .select(select[m-2:0]), .out(temp[1]) );
      mux_module #(.N(2),.m(1)) M3 (.inp(temp), .select(select[m-1]), .out(out));

    end
  endgenerate
endmodule

