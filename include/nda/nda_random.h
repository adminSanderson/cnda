#ifndef NDA_RANDOM_H
#define NDA_RANDOM_H

#include "nda/nda_core.h"

void nda_seed(unsigned int seed);
void nda_random_fill(NDArray* arr, double min, double max);
NDArray* nda_random(int ndim, const size_t* shape, double min, double max);

#endif // NDA_RANDOM_H