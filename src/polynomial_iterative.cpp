#include "include/defines.hpp"

double polynomial_iterative(float x, deque<double> terms, int max_degree)
{
    double result = 0.0f; // Initialize result

    for (int i = max_degree; i >= 0; --i)
        result = result * x + terms[i]; // Horner's method

    return result;
}