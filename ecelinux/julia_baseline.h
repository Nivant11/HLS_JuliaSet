// julia_baseline.h

#ifndef JULIA_BASELINE_H
#define JULIA_BASELINE_H

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

int juliaIterator(float real_val, float imag_val, float Cr, float Ci, int max_iteration);

#endif // JULIA_BASELINE_H