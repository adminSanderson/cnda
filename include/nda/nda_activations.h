#ifndef NDA_ACTIVATIONS_H
#define NDA_ACTIVATIONS_H

#include "nda/nda_core.h"

// =====================
// SCALAR ACTIVATIONS
// =====================

/**
 * @brief Sigmoid activation function
 * @param x Input value
 * @return 1 / (1 + e^-x), in range (0, 1)
 */
double sigmoid(double x);


/**
 * @brief Derivative of sigmoid, computed from its output
 * @param y Output of sigmoid(x), not the raw input x
 * @return y * (1 - y)
 *
 * Takes the already-activated output rather than x, since that's
 * what's typically available during backpropagation.
 */
double sigmoid_deriv_from_output(double y); // y = sigmoid(x)

/**
 * @brief ReLU activation function
 * @param x Input value
 * @return x if x > 0, otherwise 0
 */
double relu(double x);

/**
 * @brief Derivative of ReLU
 * @param x Input value (raw input, not output)
 * @return 1 if x > 0, otherwise 0
 */
double relu_deriv(double x);

/**
 * @brief Hyperbolic tangent activation function
 * @param x Input value
 * @return tanh(x), in range (-1, 1)
 */
double tanh_activation(double x);

/**
 * @brief Derivative of tanh, computed from its output
 * @param y Output of tanh_activation(x), not the raw input x
 * @return 1 - y^2
 */
double tanh_deriv_from_output(double y); // y = tanh(x)

// =====================
// NDARRAY WRAPPERS
// =====================

/**
 * @brief Applies sigmoid element-wise to an array
 * @param arr Input array
 * @return New NDArray* with sigmoid applied to each element
 */
NDArray* nda_sigmoid(const NDArray* arr);

/**
 * @brief Applies the sigmoid derivative element-wise
 * @param activated_output Array of sigmoid outputs (not raw input)
 * @return New NDArray* with sigmoid_deriv_from_output applied to
 *         each element
 */
NDArray* nda_sigmoid_derivative(const NDArray* activated_output);

/**
 * @brief Applies ReLU element-wise to an array
 * @param arr Input array
 * @return New NDArray* with relu applied to each element
 */
NDArray* nda_relu(const NDArray* arr);

/**
 * @brief Applies the ReLU derivative element-wise
 * @param arr Input array (raw input, not output)
 * @return New NDArray* with relu_deriv applied to each element
 */
NDArray* nda_relu_derivative(const NDArray* arr);

/**
 * @brief Applies tanh element-wise to an array
 * @param arr Input array
 * @return New NDArray* with tanh_activation applied to each element
 */
NDArray* nda_tanh(const NDArray* arr);


/**
 * @brief Applies the tanh derivative element-wise
 * @param activated_output Array of tanh outputs (not raw input)
 * @return New NDArray* with tanh_deriv_from_output applied to
 *         each element
 */
NDArray* nda_tanh_derivative(const NDArray* activated_output);

#endif // NDA_ACTIVATIONS_H