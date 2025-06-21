#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double avaliarPolinomioIterativo(const vector<double>& coeficientes, double x) {
    /**
     * Avalia um polinômio dado seus coeficientes e um valor x de forma iterativa.
     * 
     * @param coeficientes Vetor de coeficientes do polinômio em ordem crescente de grau
     * @param x Valor no qual o polinômio será avaliado
     * @return O valor do polinômio avaliado em x
     */
    double resultado = 0.0;
    for (size_t grau = 0; grau < coeficientes.size(); ++grau) {
        resultado += coeficientes[grau] * pow(x, grau);
    }
    return resultado;
}

// Analise de complexidade: 2n ,O(n)  n= no de coeficientes 


/*
// Exemplo de uso:
int main() {
    vector<double> coeficientes = {2, -1, 3}; // Representa 2 + (-1)x + 3x²
    double x = 2.0;
    cout << "Resultado: " << avaliarPolinomioIterativo(coeficientes, x) << endl; // Resultado: 12
    return 0;
}
*/

double avaliarPolinomioRecursivo(const vector<double>& coeficientes, double x, int grau = -1) {
    /**
     * Avalia um polinômio dado seus coeficientes e um valor x de forma recursiva.
     * 
     * @param coeficientes Vetor de coeficientes do polinômio em ordem crescente de grau
     * @param x Valor no qual o polinômio será avaliado
     * @param grau Parâmetro interno para controle da recursão (não deve ser fornecido pelo usuário)
     * @return O valor do polinômio avaliado em x
     */
    if (grau == -1) {
        grau = coeficientes.size() - 1;
    }
    
    if (grau == 0) {
        return coeficientes[0];
    }
    
    return coeficientes[grau] * pow(x, grau) + avaliarPolinomioRecursivo(coeficientes, x, grau - 1);
}

/*
// Exemplo de uso:
int main() {
    vector<double> coeficientes = {2, -1, 3}; // Representa 2 + (-1)x + 3x²
    double x = 2.0;
    cout << "Resultado: " << avaliarPolinomioRecursivo(coeficientes, x) << endl; // Resultado: 12
    return 0;
}
*/

//Analise de complexidade:  ,O()  n= no de coeficientes 