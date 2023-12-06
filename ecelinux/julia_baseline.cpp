#include <iostream>

#include "julia_baseline.h"
using namespace std;

#define WIDTH 480
#define HEIGHT 640
#define MAX_ITER 1000
#define CR -0.7
#define CI 0.3

// Performs the julia iteration for a single value. Returns the number of iterations to diverge.
int juliaIterator(float real_val, float imag_val, float Cr, float Ci, int max_iteration){
    int n = 0;
    
    for (n = 0; n < max_iteration && (real_val * real_val + imag_val * imag_val <= 4); ++n) {
        float temp_real = real_val;
        real_val = real_val * real_val - imag_val * imag_val + Cr;
        imag_val = 2 * temp_real * imag_val + Ci;
    }

    return n ;
}

// int main() {
//     // TEST FOR ONE PIXEL:
//     // float real_test = 0;
//     // float imag_test = 0;

//     // int NUM_ITER = juliaIterator(real_test, imag_test, Cr, Ci, 100);
//     // std::cout << NUM_ITER << std::endl;
    
//     //initilaize pixel array
//     int pixel_array[WIDTH][HEIGHT][3];

//     // int x_arraySize = 640;
//     float x[WIDTH];
//     // int y_arraySize = 480;
//     float y[HEIGHT];

//     // Populate the array with values from -2 to 2
//     for (int i = 0; i < WIDTH; ++i) {
//         x[i] = -2.0 + i * (4.0 / (WIDTH-1));
//     }

//     // Populate the array with values from -2 to 2
//     for (int i = 0; i < HEIGHT; ++i) {
//         y[i] = -2.0 + i * (4.0 / (HEIGHT-1));
//     }
    
//     int n = 0;
//     cout << "i, " << "j, " << "x, " << "y, " << "num_iterations" << endl;
//     for (int i = 0; i < WIDTH; i++) {
//         for (int j = 0; j < HEIGHT; j++) {
//             n = juliaIterator(x[i], y[j], CR, CI, 100);
//             cout << i << ", " << j << ", " << x[i] << ", " << y[j] << ", " << n << endl;
//         }
//     }
        

//     return 0;
// }
