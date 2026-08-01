#include "nda/nda_activations.h"
#include "nda/nda_ops.h"
#include <math.h>

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_deriv_from_output(double y) {
    return y * (1.0 - y);
}

double relu(double x) {
    return x > 0.0 ? x : 0.0;
}

double relu_deriv(double x) {
    return x > 0.0 ? 1.0 : 0.0;
}

double tanh_activation(double x) {
    return tanh(x);
}

double tanh_deriv_from_output(double y) {
    return 1.0 - y * y;
}

NDArray* nda_sigmoid(const NDArray* arr) {
    return nda_map(arr, sigmoid);
}

NDArray* nda_sigmoid_derivative(const NDArray* activated_output) {
    return nda_map(activated_output, sigmoid_deriv_from_output);
}

NDArray* nda_relu(const NDArray* arr) {
    return nda_map(arr, relu);
}

NDArray* nda_relu_derivative(const NDArray* arr) {
    return nda_map(arr, relu_deriv);
}

NDArray* nda_tanh(const NDArray* arr) {
    return nda_map(arr, tanh_activation);
}

NDArray* nda_tanh_derivative(const NDArray* activated_output) {
    return nda_map(activated_output, tanh_deriv_from_output);
}