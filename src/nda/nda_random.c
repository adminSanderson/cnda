#include "nda/nda_random.h"
#include <time.h>

void nda_seed(unsigned int seed) {
    srand(seed);
}

void nda_random_fill(NDArray* arr, double min, double max) {
    if (!arr) return;

    size_t total = nda_total_size(arr);

    for (size_t i = 0; i < total; i++) {
        double r = (double)rand() / (double)RAND_MAX; // [0, 1]
        arr->data[i] = min + r * (max - min);
    }
}

NDArray* nda_random(int ndim, const size_t* shape, double min, double max) {
    NDArray* arr = nda_create(ndim, shape);
    if (!arr) return NULL;

    nda_random_fill(arr, min, max);

    return arr;
}