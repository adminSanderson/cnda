#ifndef NDA_CORE_H
#define NDA_CORE_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

// =====================
// NDARRAY STRUCT
// =====================

typedef struct {
    int ndim;
    size_t* shape;
    size_t* strides;
    double* data;
    int owns_data;
} NDArray;

// =====================
// CORE FUNCTIONS
// =====================

/**
 * @brief Creates a new N-dimensional array
 * @param ndim Number of dimensions
 * @param shape Array of dimension sizes
 * @return NDArray* or NULL on memory error
 * 
 * Allocates memory for the array structure, shape, strides,
 * and data buffer. Initializes strides in C-order (row-major).
 * Use nda_free() to deallocate.
 */
NDArray* nda_create(int ndim, const size_t* shape);

/**
 * @brief Frees an NDArray and its owned memory
 * @param arr Array to free (safe to pass NULL)
 *
 * Frees data (only if owns_data is set), shape, strides, and
 * the struct itself. Does nothing if arr is NULL.
 */
void nda_free(NDArray* arr);


/**
 * @brief Computes the total number of elements in an array
 * @param arr Array to measure
 * @return Product of all dimension sizes
 *
 * Equivalent to shape[0] * shape[1] * ... * shape[ndim-1].
 */
size_t nda_total_size(const NDArray* arr);

/**
 * @brief Checks whether two arrays have identical shapes
 * @param a First array
 * @param b Second array
 * @return 1 if ndim and every dimension match, 0 otherwise
 *
 * Does not compare data, only shape. Used to validate operations
 * that require matching dimensions (no broadcasting).
 */
int nda_same_shape(const NDArray* a, const NDArray* b);


/**
 * @brief Fills every element of an array with a scalar value
 * @param arr Array to fill (modified in place)
 * @param value Value to assign to every element
 * @return The same arr pointer, or NULL if arr is NULL
 */
NDArray* nda_fill(NDArray* arr, double value);

/**
 * @brief Creates a new array filled with zeros
 * @param ndim Number of dimensions
 * @param shape Array of dimension sizes
 * @return New NDArray* filled with 0.0, or NULL on memory error
 */
NDArray* nda_zeros(int ndim, const size_t* shape);

/**
 * @brief Creates a new array filled with ones
 * @param ndim Number of dimensions
 * @param shape Array of dimension sizes
 * @return New NDArray* filled with 1.0, or NULL on memory error
 */
NDArray* nda_ones(int ndim, const size_t* shape);

/**
 * @brief Creates a deep copy of an array
 * @param arr Array to copy
 * @return New independent NDArray* with the same shape and data,
 *         or NULL on memory error
 *
 * The copy owns its own data buffer; modifying it does not affect
 * the original.
 */
NDArray* nda_copy(NDArray* arr);

/**
 * @brief Creates an identity matrix
 * @param size Number of rows/columns (square matrix)
 * @return New size x size NDArray* with 1.0 on the main diagonal and
 *         0.0 elsewhere, or NULL on memory error
 */
NDArray* nda_eye(size_t size);

#endif // NDA_CORE_H