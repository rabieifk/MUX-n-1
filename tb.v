module tb_MUX_w4();
  reg [3:0] a, b, c, d;
  reg [1:0] select;
  wire [3:0] out;
  
  w_bit_N_MUX #(.N(4), .m(2), .W(4)) U1 (.a3(a), .a2(b), .a1(c), .a0(d), .sel(select), .out(out));
  
  initial begin
    a = 4'b0000;
    b = 4'b0000;
    c = 4'b0001;
    d = 4'b0000;
    select = 2'b00;
    #20;
    
    a = 4'b0001;
    b = 4'b0000;
    c = 4'b0000;
    d = 4'b0000;
    select = 2'b00;
    #20;
    
    a = 4'b0000;
    b = 4'b0001;
    c = 4'b0000;
    d = 4'b0001;
    select = 2'b00;
    #20;
    
    a = 4'b0101;
    b = 4'b0100;
    c = 4'b0100;
    d = 4'b0100;
    select = 2'b10;
    #20;
    
    a = 4'b0001;
    b = 4'b1000;
    c = 4'b0000;
    d = 4'b1000;
    select = 2'b11;
    #20;
    
    
  end
endmodule
