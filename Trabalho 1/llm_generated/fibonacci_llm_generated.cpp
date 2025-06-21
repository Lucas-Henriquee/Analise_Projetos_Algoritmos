#include <iostream>

using namespace std;

unsigned long long fibonacciIterativo(int n) {
    /**
     * Calcula o n-ésimo termo da sequência de Fibonacci de forma iterativa.
     * 
     * @param n Índice do termo desejado (começando de 0)
     * @return O n-ésimo termo da sequência de Fibonacci
     */
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    unsigned long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; ++i) {
        temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}

//Analise de complexidade: 3(n-2)+2 ,O(n)  n= no de termos

/*
// Exemplo de uso:
int main() {
    int n = 6;
    cout << "Fibonacci(" << n << ") = " << fibonacciIterativo(n) << endl; // Resultado: 8
    return 0;
}
*/

unsigned long long fibonacciRecursivo(int n) {
    /**
     * Calcula o n-ésimo termo da sequência de Fibonacci de forma recursiva.
     * 
     * @param n Índice do termo desejado (começando de 0)
     * @return O n-ésimo termo da sequência de Fibonacci
     */
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

/*
// Exemplo de uso:
int main() {
    int n = 6;
    cout << "Fibonacci(" << n << ") = " << fibonacciRecursivo(n) << endl; // Resultado: 8
    return 0;
}
*/

//Analise de complexidade: (2^n)+1 ,O(2^n)  n= no de termos