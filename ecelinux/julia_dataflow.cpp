#include <iostream>
#include <hls_stream.h>
#include <cstdint>
#include "julia_dataflow.h"
using namespace std;

// The union type is the trick to the conversion
union streamVal {
  float fl;
  uint32_t u32;
};

// Dispatch inputs to PEs
// We can get rid of x and y arrays
void dispatch(hls::stream<float> real_val[PE_NUM], hls::stream<float> imag_val[PE_NUM], hls::stream<bit32_t> &strm_in) {
    // Loop through the input stream and distribute values to real_val and imag_val streams
    DISPATCH_LOOP:
    for (int i = 0; i < (WIDTH*HEIGHT); ++i) {
        // Read real and imaginary values from the input stream
        uint32_t real_value = strm_in.read();
        streamVal r_val = {.u32 = real_value}; // Init Union for real value
        uint32_t imag_value = strm_in.read(); 
        streamVal i_val = {.u32 = imag_value}; // Init Union for image value

        // Determine the index of the stream to write to
        int pe_index = i % PE_NUM;

        // Write values to the corresponding streams
        real_val[pe_index].write(r_val.fl);
        imag_val[pe_index].write(i_val.fl);
    }

}
    
// Performs the julia iteration for a single value. Puts the number of iterations to diverge in another stream.
// Processing Element
void juliaIterator(hls::stream <float> &real_val, hls::stream <float> &imag_val, float Cr, float Ci, int max_iteration, hls::stream <int>&num_iter){
    int n = 0;
    // if(real_val.empty() || img_val.empty()){
    //     return;
    // }
    float real;
    real_val.read(real);
    float imag;
    imag_val.read(imag);
    
    JULIA_ITERATOR_LOOP:
    // #pragma pipeline
    for (n = 0; n < max_iteration && (real * real + imag * imag <= 4); ++n) {
        float temp_real = real;
        real = real * real - imag * imag + Cr;
        imag = 2 * temp_real * imag + Ci;
    }

    num_iter.write(n);
}

void merge(hls::stream<int> num_iter[PE_NUM], hls::stream<bit32_t>& output_stream) {
    // Iterate over each stream
    MERGE_OUTERLOOP:
    // #pragma pipeline
    int value;
    int cnt = 0;
    while (cnt < (WIDTH * HEIGHT)){
        for (int pe = 0; pe < PE_NUM; ++pe) { //****need to get rid of for loop*****
            // Iterate over each element in the stream
            // Read value from the current stream
            if (num_iter[pe].read_nb(value)){
                // Write the value to the output stream
                output_stream.write(value);
                cnt++;
            }
            
        }
    }
}

//main function
void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out) {
    #pragma HLS dataflow
    // Partition 
    hls::stream<float> real_val[PE_NUM];
    hls::stream<float> imag_val[PE_NUM];
    hls::stream<int>   num_iter[PE_NUM];

    #pragma HLS stream variable=real_val depth=4 //real FIFO depth is depth-1
    #pragma HLS stream variable=imag_val depth=4 //real FIFO depth is depth-1
    #pragma HLS stream variable=num_iter depth=4

    // Dispatch real and imaginary values into the streams
    dispatch(real_val, imag_val, strm_in);
    
    // Call the Iterator for each pixel in each stream
    DUT_LOOP:
    // #pragma pipeline
    for (int i = 0; i < (WIDTH*HEIGHT)/PE_NUM; i++){
        juliaIterator(real_val[0], imag_val[0], CR, CI, MAX_ITER, num_iter[0]);
        juliaIterator(real_val[1], imag_val[1], CR, CI, MAX_ITER, num_iter[1]);
    //     JULIA_LOOP:
    //     for (int j = 0; j < PE_NUM; j ++) {
    //         juliaIterator(real_val[j], imag_val[j], CR, CI, MAX_ITER, num_iter[j]);
    //     }
    }

    
    merge(num_iter, strm_out);

}