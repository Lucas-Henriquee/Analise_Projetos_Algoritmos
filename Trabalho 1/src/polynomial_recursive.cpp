#include "../include/defines.hpp"

double polynomial_recursive(deque<double> terms, double x)
{
    if (terms.size() == 0)
        return 0.0f; // Base case: if degree exceeds the number of terms

    double term = terms.front();
    terms.pop_front();

    double result = x * polynomial_recursive(terms, x);

    terms.push_front(term); // Restore the term for further calculations
    result += term;         // Add the current term to the result

    return result;
}