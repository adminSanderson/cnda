#ifndef NDA_OPS_H
#define NDA_OPS_H

#include "nda/nda_core.h"

// =====================
// BROADCASTABLE ARITHMETIC
// =====================

NDArray* nda_add(const NDArray* a, const NDArray* b);
NDArray* nda_sub(const NDArray* a, const NDArray* b);
NDArray* nda_mul(const NDArray* a, const NDArray* b);
NDArray* nda_div(const NDArray* a, const NDArray* b);

// =====================
// LINEAR ALGEBRA
// =====================

NDArray* nda_matmul(const NDArray* a, const NDArray* b);
NDArray* nda_transpose(const NDArray* arr);

// =====================
// SCALAR OPS
// =====================

NDArray* nda_scalar_add(const NDArray* arr, double scalar);
NDArray* nda_scalar_mul(const NDArray* arr, double scalar);

// =====================
// FUNCTIONAL / REDUCTIONS
// =====================

NDArray* nda_map(const NDArray* arr, double (*fn)(double));
// NDArray* nda_sum_axis(const NDArray* arr, int axis);
// double   nda_sum_all(const NDArray* arr);

// =====================
// IO
// =====================

void nda_print(const NDArray* arr, int precision);

#endif // NDA_OPS_H