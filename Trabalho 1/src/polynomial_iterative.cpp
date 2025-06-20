#include "../include/defines.hpp"

double polynomial_iterative(double x, deque<double> terms)
{
    double result = 0.0f; // Initialize result

    for (int i = terms.size() - 1; i >= 0; --i)
        result = result * x + terms[i]; // Horner's method

    return result;
}