#include "../include/defines.hpp"

int fibonacci_iterative(int n)
{

    int a = 0, b = 1;

    for (int i = 0; i < n; i++)
    {
        int temp = a;
        a = b;
        b += temp;
    }

    return a;
}