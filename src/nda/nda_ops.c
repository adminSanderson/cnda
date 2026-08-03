#include "nda/nda_ops.h"
#include <math.h>

typedef enum {
    NDA_OP_ADD,
    NDA_OP_SUB,
    NDA_OP_MUL,
    NDA_OP_DIV
} NDArrayOp;

static NDArray* nda_broadcast_op(const NDArray* a, const NDArray* b, NDArrayOp op);

NDArray* nda_add(const NDArray* a, const NDArray* b) {
    return nda_broadcast_op(a, b, NDA_OP_ADD);
}

NDArray* nda_sub(const NDArray* a, const NDArray* b) {
    return nda_broadcast_op(a, b, NDA_OP_SUB);
}

NDArray* nda_mul(const NDArray* a, const NDArray* b) {
    return nda_broadcast_op(a, b, NDA_OP_MUL);
}

NDArray* nda_div(const NDArray* a, const NDArray* b) {
    return nda_broadcast_op(a, b, NDA_OP_DIV);
}

NDArray* nda_matmul(const NDArray* a, const NDArray* b) {
    if (!a || !b) return NULL;
    if (a->ndim != 2 || b->ndim != 2) return NULL;
    if (a->shape[1] != b->shape[0]) return NULL;  // M×K на K×N

    size_t M = a->shape[0];
    size_t K = a->shape[1];
    size_t N = b->shape[1];

    size_t shape[2] = {M, N};
    NDArray* result = nda_create(2, shape);
    if (!result) return NULL;

    nda_fill(result, 0.0);

    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            for (size_t k = 0; k < K; k++) {
                result->data[i * N + j] += a->data[i * K + k] * b->data[k * N + j];
            }
        }
    }

    return result;
}

NDArray* nda_transpose(const NDArray* arr) {
    if (!arr) return NULL;
    if (arr->ndim != 2) return NULL;

    size_t shape[2] = {arr->shape[1], arr->shape[0]};
    NDArray* result = nda_create(2, shape);
    if (!result) return NULL;

    for (size_t i = 0; i < arr->shape[0]; i++) {
        for (size_t j = 0; j < arr->shape[1]; j++) {
            result->data[j * shape[1] + i] = arr->data[i * arr->shape[1] + j];
        }
    }

    return result;
}

NDArray* nda_scalar_add(const NDArray* arr, double scalar) {
    if (!arr) return NULL;

    NDArray* result = nda_create(arr->ndim, arr->shape);
    if (!result) return NULL;

    size_t total = nda_total_size(arr);

    for (size_t i = 0; i < total; i++) {
        result->data[i] = arr->data[i] + scalar;
    }

    return result;
}

NDArray* nda_scalar_mul(const NDArray* arr, double scalar) {
    if (!arr) return NULL;

    NDArray* result = nda_create(arr->ndim, arr->shape);
    if (!result) return NULL;

    size_t total = nda_total_size(arr);

    for (size_t i = 0; i < total; i++) {
        result->data[i] = arr->data[i] * scalar;
    }

    return result;
}

NDArray* nda_map(const NDArray* arr, double (*fn)(double)) {
    if (!arr || !fn) return NULL;

    NDArray* result = nda_create(arr->ndim, arr->shape);
    if (!result) return NULL;

    size_t total = nda_total_size(arr);

    for (size_t i = 0; i < total; i++) {
        result->data[i] = fn(arr->data[i]);
    }

    return result;
}

double nda_sum_all(const NDArray* arr) {
    if (!arr) return 0.0;

    double s = 0.0;
    size_t total = nda_total_size(arr);

    for (size_t i = 0; i < total; i++) {
        s += arr->data[i];
    }

    return s;
}

void nda_print(const NDArray* arr, int precision) {
    if (!arr) {
        printf("[NDA]: NDArray(NULL)\n");
        return;
    }

    if (arr->ndim == 1) {
        for (size_t i = 0; i < arr->shape[0]; i++) {
            printf("%.*f", precision, arr->data[i]);

            if (i + 1 < arr->shape[0]) {
                printf(", ");
            }
        }
        printf("\n");
        return;
    } else if (arr->ndim == 2) {
        for (size_t i = 0; i < arr->shape[0]; i++) {
            for (size_t j = 0; j < arr->shape[1]; j++) {
                printf("%.*f", precision, arr->data[i * arr->shape[1] + j]);

                if (j + 1 < arr->shape[1]) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        return;
    }

    printf("[nda_print]: ndim > 2 not supported yet\n");
}

static NDArray* nda_broadcast_op(const NDArray* a, const NDArray* b, NDArrayOp op) {
    if (!a || !b) return NULL;

    int result_ndim = (a->ndim > b->ndim) ? a->ndim : b->ndim;

    size_t a_vir[result_ndim];
    size_t b_vir[result_ndim];
    size_t result_shape[result_ndim];
    size_t a_strides_vir[result_ndim];
    size_t b_strides_vir[result_ndim];

    int a_offset = result_ndim - a->ndim;
    int b_offset = result_ndim - b->ndim;

    for (int i = 0; i < result_ndim; i++) {
        a_vir[i] = (i < a_offset) ? 1 : a->shape[i - a_offset];
        b_vir[i] = (i < b_offset) ? 1 : b->shape[i - b_offset];

        if (a_vir[i] != b_vir[i] && a_vir[i] != 1 && b_vir[i] != 1) return NULL;
        
        result_shape[i] = (a_vir[i] > b_vir[i]) ? a_vir[i] : b_vir[i];
        a_strides_vir[i] = (i < a_offset || a_vir[i] == 1) ? 0 : a->strides[i - a_offset] / sizeof(double);
        b_strides_vir[i] = (i < b_offset || b_vir[i] == 1) ? 0 : b->strides[i - b_offset] / sizeof(double);
    }

    NDArray* result = nda_create(result_ndim, result_shape);
    if (!result) return NULL;

    size_t result_total_size = nda_total_size(result);
    size_t idx[result_ndim];

    for (size_t k = 0; k < result_total_size; k++) {
        size_t rem = k;
        for (int dim = result_ndim - 1; dim >= 0; dim--) {
            idx[dim] = rem % result_shape[dim];
            rem /= result_shape[dim];
        }

        size_t a_data_offset = 0;
        size_t b_data_offset = 0;

        for (int dim = 0; dim < result_ndim; dim++) {
            a_data_offset += idx[dim] * a_strides_vir[dim];
            b_data_offset += idx[dim] * b_strides_vir[dim];
        }

        double a_val = a->data[a_data_offset];
        double b_val = b->data[b_data_offset];

        switch (op) {
            case NDA_OP_ADD:
                result->data[k] = a_val + b_val;
                break;
            case NDA_OP_SUB:
                result->data[k] = a_val - b_val;
                break;
            case NDA_OP_MUL:
                result->data[k] = a_val * b_val;
                break;
            case NDA_OP_DIV:
                if (b_val > -1e-12 && b_val < 1e-12) result->data[k] = 1e308;
                else result->data[k] = a_val / b_val;
                break;
        }
    }

    return result;
}

double nda_determinant(const NDArray* arr) {
    if (!arr || arr->ndim != 2 || arr->shape[0] != arr->shape[1]) return NAN;

    int n = (int)arr->shape[0];

    switch (n) {
        case 1:
            return arr->data[0];
        case 2:
            return arr->data[0] * arr->data[3] - arr->data[1] * arr->data[2];
        case 3: {
            double a = arr->data[0], b = arr->data[1], c = arr->data[2];
            double d = arr->data[3], e = arr->data[4], f = arr->data[5];
            double g = arr->data[6], h = arr->data[7], i = arr->data[8];
            return a * (e*i - f*h) - b * (d*i - f*g) + c * (d*h - e*g);
        }
        default: {
            NDArray* L = nda_eye(n);
            NDArray* U = nda_eye(n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0;
                    if (i <= j) {
                        for (int k = 0; k < i; k++) sum += L->data[i*n+k] * U->data[k*n+j];
                        U->data[i*n+j] = arr->data[i*n+j] - sum;
                    } else {
                        for (int k = 0; k < j; k++) sum += L->data[i*n+k] * U->data[k*n+j];
                        L->data[i*n+j] = (arr->data[i*n+j] - sum) / U->data[j*n+j];
                    }
                }
            }

            double ans = 1;
            for (int i = 0; i < n; i++) ans *= L->data[i*n+i] * U->data[i*n+i];

            nda_free(L);
            nda_free(U);
            return ans;
        }
    }
}