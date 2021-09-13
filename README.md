# MUX-n-1
W-bit N-to-1 multiplexer Verilog implementation

Cpp code is developed to generate a verilog code for a multiplexer with arbitary input width and input number.
Also there is a test file to test the Cpp code.

You can run the Cpp code with:
>g++ Gen_MUX_Vlog.c++ -o Gen_MUX_Vlog 

and then:

>Gen_MUX_Vlog.exe -n N -w W

N and W can be any integer number.
