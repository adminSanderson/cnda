#ifndef NDA_OPS_H
#define NDA_OPS_H

#include "nda/nda_core.h"

// =====================
// BROADCASTABLE ARITHMETIC
// =====================

/**
 * @brief Element-wise addition with broadcasting
 * @param a First array
 * @param b Second array
 * @return New NDArray* with the broadcast result, or NULL if
 *         shapes are incompatible
 */
NDArray* nda_add(const NDArray* a, const NDArray* b);

/**
 * @brief Element-wise subtraction with broadcasting
 * @param a Array to subtract from
 * @param b Array to subtract
 * @return New NDArray* with the broadcast result, or NULL if
 *         shapes are incompatible
 */
NDArray* nda_sub(const NDArray* a, const NDArray* b);

/**
 * @brief Element-wise multiplication with broadcasting
 * @param a First array
 * @param b Second array
 * @return New NDArray* with the broadcast result, or NULL if
 *         shapes are incompatible
 */
NDArray* nda_mul(const NDArray* a, const NDArray* b);

/**
 * @brief Element-wise division with broadcasting
 * @param a Numerator array
 * @param b Denominator array
 * @return New NDArray* with the broadcast result, or NULL if
 *         shapes are incompatible
 *
 * Division where |b| < 1e-12 returns 1e308 for that element
 * instead of inf/nan, regardless of the sign of the numerator
 * (i.e. -5 / 0 also returns 1e308, not -1e308).
 */
NDArray* nda_div(const NDArray* a, const NDArray* b);

// =====================
// LINEAR ALGEBRA
// =====================

/**
 * @brief Matrix multiplication of two 2D arrays
 * @param a Left matrix (M x K)
 * @param b Right matrix (K x N)
 * @return New M x N NDArray*, or NULL if either array is not 2D
 *         or inner dimensions don't match (a->shape[1] != b->shape[0])
 */
NDArray* nda_matmul(const NDArray* a, const NDArray* b);

/**
 * @brief Transposes a 2D array
 * @param arr Array to transpose (M x N)
 * @return New N x M NDArray*, or NULL if arr is not 2D
 */
NDArray* nda_transpose(const NDArray* arr);

/**
 * @brief Computes the determinant of a square matrix
 * @param arr Square 2D array (n x n)
 * @return The determinant, or NAN if arr is not a square 2D matrix
 *
 * Uses closed-form formulas for n = 1, 2, 3, and LU decomposition
 * without pivoting for n > 3. Without pivoting, the LU path can
 * return nan on singular or near-singular matrices where a zero
 * appears on the diagonal of U mid-computation.
 */
double nda_determinant(const NDArray* arr);

// =====================
// SCALAR OPS
// =====================

/**
 * @brief Adds a scalar to every element
 * @param arr Array to add to
 * @param scalar Value to add
 * @return New NDArray* with the same shape as arr, or NULL on
 *         memory error
 */
NDArray* nda_scalar_add(const NDArray* arr, double scalar);

/**
 * @brief Multiplies every element by a scalar
 * @param arr Array to multiply
 * @param scalar Value to multiply by
 * @return New NDArray* with the same shape as arr, or NULL on
 *         memory error
 */
NDArray* nda_scalar_mul(const NDArray* arr, double scalar);

// =====================
// FUNCTIONAL / REDUCTIONS
// =====================

/**
 * @brief Applies a scalar function to every element
 * @param arr Array to map over
 * @param fn Function taking and returning a double
 * @return New NDArray* with the same shape as arr, where each
 *         element is fn(arr[i]), or NULL if arr or fn is NULL
 *
 * Used internally by the activation functions (nda_sigmoid,
 * nda_relu, nda_tanh) to apply their scalar form element-wise.
 */
NDArray* nda_map(const NDArray* arr, double (*fn)(double));

// NDArray* nda_sum_axis(const NDArray* arr, int axis);
// double   nda_sum_all(const NDArray* arr);

// =====================
// IO
// =====================

/**
 * @brief Prints an array to stdout
 * @param arr Array to print (1D or 2D only)
 * @param precision Number of decimal places to display
 *
 * 1D arrays print as a single comma-separated line. 2D arrays
 * print as rows of space-separated values. Arrays with ndim > 2
 * are not supported and print a placeholder message.
 */
void nda_print(const NDArray* arr, int precision);

#endif // NDA_OPS_H