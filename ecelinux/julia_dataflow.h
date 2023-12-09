// julia_dataflow.h

#ifndef JULIA_DATAFLOW_H
#define JULIA_DATAFLOW_H

#include <hls_stream.h>
#include "ap_int.h"


#define WIDTH 640
#define HEIGHT 480
#define MAX_ITER 1000
#define CR -0.7
#define CI 0.3
#define PE_NUM 32

typedef ap_uint<32> bit32_t;

/**
 * Calculates the number of iterations for a given complex point in the Julia set.
 *
 * @param real_val The real part of the complex number.
 * @param imag_val The imaginary part of the complex number.
 * @param Cr The real part of the constant complex number.
 * @param Ci The imaginary part of the constant complex number.
 * @param TERMINATION The maximum number of iterations.
 * @return The number of iterations before the complex number escapes.
*/  

void dispatch(hls::stream<float> real_val[PE_NUM], hls::stream<float> imag_val[PE_NUM], hls::stream<bit32_t> &strm_in) ;
void juliaIterator(hls::stream <float> &real_val, hls::stream <float> &imag_val, float Cr, float Ci, int max_iteration, hls::stream<int> &num_iter);
void merge(hls::stream<int> num_iter[PE_NUM], hls::stream<bit32_t>& output_stream);
void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);


#endif 