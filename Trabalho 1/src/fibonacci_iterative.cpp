#include "../include/defines.hpp"

size_t fibonacci_iterative(int n)
{
    if (n <= 1)
        return n;

    size_t a = 0, b = 1;

    while (n > 1)
    {
        b = a + b;
        a = b - a;
        --n;
    }

    return b;
}
