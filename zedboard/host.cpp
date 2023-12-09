#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<math.h>
#include<assert.h>

#include<iostream>
#include<fstream>

#include "host.h"
#include "ap_int.h"
#include "timer.h"

using namespace std;


union streamVal { 
  float fl;
  uint32_t u32;
};

int main() {

    // Open channels to the FPGA board.
    // These channels appear as files to the Linux OS
    int fdr = open("/dev/xillybus_read_32", O_RDONLY);
    int fdw = open("/dev/xillybus_write_32", O_WRONLY);

    int nbytes;

    if ((fdr < 0) || (fdw < 0)) {
        fprintf (stderr, "Failed to open Xillybus device channels\n");
        exit(-1);
    }

    Timer timer("JuliaSet ");

    timer.start();

    // Populate the array with values from -2 to 2
    for (int i = 0; i < WIDTH; ++i) {
        float w_val = -2.0 + i * (4.0/(WIDTH - 1));
        streamVal w_int = {.fl = w_val};
        for (int j = 0; j < HEIGHT; ++j) {
            float h_val = -2.0 + j * (4.0 / (HEIGHT - 1));
            streamVal h_int = {.fl = h_val};
            nbytes = write (fdw, (void*)&w_int.u32, sizeof(w_int.u32));
            assert (nbytes == sizeof(w_int.u32));
            nbytes = write (fdw, (void*)&h_int.u32, sizeof(h_int.u32));
            assert (nbytes == sizeof(w_int.u32));
        }
    }

    std::ofstream outputFile("output/dataflow_output.txt");
    for (int i = 0; i< WIDTH*HEIGHT; i++){
        uint32_t s_out;
        nbytes = read (fdr, (void*)&s_out, sizeof(s_out));
        outputFile << s_out << " \n";
    }

    timer.stop();

    outputFile.close();

    close(fdw);
    close(fdr);

    return 0;
}
