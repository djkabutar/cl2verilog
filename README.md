**OpenCL kernel to Verilog**

The project initiative is to convert OpenCL like backend APIs to Verilog
therefore on the FPGAs on time reconfiguration can be made.

First ideation for the project is to make Source to Source comiler.
For that we are using the C Language to accomplish the task.

For the intiation of the project the we are going to use the UART as
the communication between processor and FPGA so the data communication
for initial phase can be done, we can move towards any other protocol 
but for the proof of concept we will use UART.

It can be used on the any FPGA and processor as it is using simple 
UART right now.
