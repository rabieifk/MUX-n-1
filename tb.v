module tb_mux();
  reg [15:0] in;
  reg [3:0] sel;
  wire out;
  
  MUX_n-to-1 #(.N(16), .m($clog2(16))) U1 (.inp(in), .select(sel), .out(out));
  
  initial begin
    in = 16'b0000000000000000;
    sel = 4'b0000;
    #20
    
    in = 16'b0000000000000001;
    sel = 4'b0000;
    #20
    
    in = 16'b0000000000000001;
    sel = 4'b0001;
    #20
    
    in = 16'b1000000000000001;
    sel = 4'b1111;
    #20
    
    in = 16'b0000000100000001;
    sel = 4'b1001;
    #20
    
    in = 16'b0000000000000001;
    sel = 4'b0101;
    #20;
    
  end
endmodule
