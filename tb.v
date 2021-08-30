module tb_mux();
  reg [13:0] in;
  reg [3:0] sel;
  wire out;
  
  MUX_n #(.N(16), .m($clog2(16))) U1 (.inp(in), .select(sel), .out(out));
  
  initial begin
    in = 14'b00000000000000;
    sel = 4'b0000;
    #20
    
    in = 14'b00000000000001;
    sel = 4'b0000;
    #20
    
    in = 14'b00000000000001;
    sel = 4'b0001;
    #20
    
    in = 14'b10000000000001;
    sel = 4'b1101;
    #20
    
    in = 14'b00000100000001;
    sel = 4'b1001;
    #20
    
    in = 16'b00000001000001;
    sel = 4'b0101;
    #20;
    
  end
endmodule
