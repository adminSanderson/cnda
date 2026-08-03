#include <stdio.h>
#include "cnda.h"

int main() {
    size_t shape[2] = {4, 4};
    NDArray* diag = nda_zeros(2, shape);
    diag->data[0*4+0] = 2;
    diag->data[1*4+1] = 3;
    diag->data[2*4+2] = 4;
    diag->data[3*4+3] = 5;
    printf("diag det (expect 120.00): %.2f\n", nda_determinant(diag));
    nda_free(diag);

    return 0;
}