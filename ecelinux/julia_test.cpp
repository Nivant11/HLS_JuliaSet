#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "julia_baseline.h"

using namespace std;

void testIterator(float real, float imag, float Cr, float Ci, int maxIter, const string& testName) {
    int iterCount = juliaIterator(real, imag, Cr, Ci, maxIter);
    cout << "Test: " << testName << " | "
         << "Complex: (" << real << ", " << imag << "), C: (" << Cr << ", " << Ci << "), "
         << "Max Iterations: " << maxIter << " | "
         << "Iterations: " << iterCount << endl;
}

int main() {
    // Test cases
    testIterator(0.3, 0.6, -0.7, 0.3, 1000, "Test 1");
    testIterator(-0.8, 0.156, -0.7, 0.3, 1000, "Test 2");
    testIterator(0.1, -0.9, -0.7, 0.3, 1000, "Test 3");
    testIterator(0, 0, -0.7, 0.3, 1000, "Test 4");
    
    // More test cases if needed

    return 0;
}