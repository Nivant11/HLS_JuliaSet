#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <hls_stream.h>
#include "julia_dataflow.h"
#include "ap_int.h"

using namespace std;


union streamVal { 
  float fl;
  uint32_t u32;
};

int main() {

    hls::stream<bit32_t> strm_in;
    hls::stream<bit32_t> strm_out;
    
    // Populate the array with values from -2 to 2
    for (int i = 0; i < WIDTH; ++i) {
        float w_val = -2.0 + i * (4.0/(WIDTH - 1));
        streamVal w_int = {.fl = w_val};
        for (int j = 0; j < HEIGHT; ++j) {
            float h_val = -2.0 + j * (4.0 / (HEIGHT - 1));
            streamVal h_int = {.fl = h_val};
            strm_in.write(w_int.u32);
            strm_in.write(h_int.u32);
        }
    }

    if(!strm_in.empty()){
        dut(strm_in, strm_out);
    }
    
    std::ofstream outputFile("output/dataflow_output.txt");
    while (!strm_out.empty()) {
        int value = strm_out.read();
        outputFile << value << " \n";
    }
    outputFile.close();

    return 0;
}