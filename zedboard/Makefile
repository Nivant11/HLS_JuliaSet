#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the cordic program
#
# @desc: 1. "make" or "make fpga" invokes the HW accelerator
#        2. "make fpga_batch" invokes the HW accelerator using batch mode
#        3. "make clean" cleans up the directory


# XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
# XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
# VHLS_INC=$(XILINX_VIVADO)/include
# # Specify compilation flags
# CFLAGS=-g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB -std=c++11 

INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH}

all: sw

sw: cordic.cpp cordic_test.cpp
	@echo "Compiling & executing cordic software program on ARM ..."
	g++ ${CFLAGS} cordic.cpp cordic_test.cpp -o cordic-arm
	./cordic-arm

fpga: host.cpp
	@echo "Compiling host program & running CORDIC accelerator ..."
	g++ -I${INC_PATH} $< -o julia_dataflow-fpga
	./julia_dataflow-fpga

fpga_batch: host_batch.cpp
	@echo "Compiling host program (batch) & running CORDIC accelerator ..."
	g++ -I${INC_PATH} $< -o cordic-fpga-batch
	./cordic-fpga-batch

clean:
	@echo "Clean up output files"
	rm -f cordic-fpga cordic-fpga-batch  *.dat
