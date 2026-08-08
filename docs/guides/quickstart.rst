Quick Start
===========

Basic Usage
-----------

Here's a simple example to get started:

.. code-block:: c

   #include "cnda.h"

   int main() {
       // Create a 3x4 matrix of zeros
       size_t shape[2] = {3, 4};
       NDArray* matrix = nda_zeros(2, shape);

       // Print the matrix
       nda_print(matrix, 2);

       // Free memory
       nda_free(matrix);

       return 0;
   }

Creating Arrays
---------------

Create arrays filled with specific values:

.. code-block:: c

   // Zeros
   NDArray* zeros = nda_zeros(2, (size_t[]){3, 4});

   // Ones
   NDArray* ones = nda_ones(2, (size_t[]){3, 4});

   // Identity matrix
   NDArray* identity = nda_eye(4);

   // Random values [0, 1)
   nda_seed(42);
   NDArray* random = nda_random(2, (size_t[]){3, 4}, 0.0, 1.0);

Matrix Operations
-----------------

.. code-block:: c

   // Matrix multiplication
   NDArray* result = nda_matmul(A, B);

   // Transpose
   NDArray* transposed = nda_transpose(matrix);

   // Element-wise operations
   NDArray* sum = nda_add(A, B);
   NDArray* product = nda_mul(A, B);

Activation Functions
--------------------

.. code-block:: c

   NDArray* activated = nda_sigmoid(layer_output);
   NDArray* gradient = nda_sigmoid_derivative(activated);

   // Also available: ReLU, Tanh