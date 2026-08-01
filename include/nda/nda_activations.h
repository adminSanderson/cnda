#ifndef NDA_ACTIVATIONS_H
#define NDA_ACTIVATIONS_H

#include "nda/nda_core.h"

// =====================
// SCALAR ACTIVATIONS
// =====================

double sigmoid(double x);
double sigmoid_deriv_from_output(double y); // y = sigmoid(x)

double relu(double x);
double relu_deriv(double x);

double tanh_activation(double x);
double tanh_deriv_from_output(double y); // y = tanh(x)

// =====================
// NDARRAY WRAPPERS
// =====================

NDArray* nda_sigmoid(const NDArray* arr);
NDArray* nda_sigmoid_derivative(const NDArray* activated_output);

NDArray* nda_relu(const NDArray* arr);
NDArray* nda_relu_derivative(const NDArray* arr);

NDArray* nda_tanh(const NDArray* arr);
NDArray* nda_tanh_derivative(const NDArray* activated_output);

#endif // NDA_ACTIVATIONS_H