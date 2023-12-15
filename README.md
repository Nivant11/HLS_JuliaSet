Running our design

in ecelinux/

make julia_dataflow //compile design

vivado_hls -f run_dataflow.tcl //tcl file for design

in either ecelinux/ or zedboard/ (not on the class server)

python3 display_.py //generate image

generating bitstream and porting to zedboard follow similar steps as in lab 4
