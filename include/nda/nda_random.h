#ifndef NDA_RANDOM_H
#define NDA_RANDOM_H

#include "nda/nda_core.h"

/**
 * @brief Seeds the random number generator
 * @param seed Seed value
 *
 * Wraps srand(). Call once before generating random arrays if
 * reproducible output is needed; the same seed always produces
 * the same sequence of values.
 */
void nda_seed(unsigned int seed);

/**
 * @brief Fills an existing array with uniform random values
 * @param arr Array to fill (modified in place)
 * @param min Lower bound (inclusive)
 * @param max Upper bound (inclusive)
 *
 * Does nothing if arr is NULL. Uses rand(), so call nda_seed()
 * beforehand for reproducibility.
 */
void nda_random_fill(NDArray* arr, double min, double max);

/**
 * @brief Creates a new array filled with uniform random values
 * @param ndim Number of dimensions
 * @param shape Array of dimension sizes
 * @param min Lower bound (inclusive)
 * @param max Upper bound (inclusive)
 * @return New NDArray* with random values, or NULL on memory error
 */
NDArray* nda_random(int ndim, const size_t* shape, double min, double max);

#endif // NDA_RANDOM_H