#include "../include/defines.hpp"

size_t fibonacci_recursive(int n)
{
    if (n <= 1)
        return n;

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}