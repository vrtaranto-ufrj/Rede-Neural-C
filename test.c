#include <stdio.h>

#include "rede_neural.h"
#include "read_iris.h"

int main(int argc, char const *argv[]) {
    Matriz *x, *y;

    preenche_matrizes_iris("iris.data", &x, &y);
    // print_matriz(x);
    // print_matriz(y);


    size_t camadas[] = {4UL, 10UL, 3UL};
    size_t num_camadas = sizeof(camadas) / sizeof(size_t);
    float X[5][2] = {
        {0.8, 0.7},
        {0.1, 0.1},
        {0.2, 0.6},
        {0.9, 0.2},
        {0.0, 0.8}
    };

    float X_test[5][2] = {
        {0.8, 0.7},
        {0.1, 0.1},
        {0.2, 0.6},
        {0.9, 0.2},
        {0.0, 0.8}
    };

    float Y[5][2] = {
        {0.70, 0.50},
        {0.21, 0.29},
        {0.32, 0.81},
        {0.38, 0.02},
        {0.20, 0.50}
    };

    Matriz *X_entrada = inicializa_matriz(5, 2);
    Matriz *Y_saida = inicializa_matriz(5, 2);
    Matriz *X_entrada_test = inicializa_matriz(5, 2);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            set_elemento_matriz(X_entrada, i, j, X[i][j]);
            set_elemento_matriz(Y_saida, i, j, Y[i][j]);
            set_elemento_matriz(X_entrada_test, i, j, X_test[i][j]);
        }
    }
    // print_matriz(X_entrada);
    // print_matriz(Y_saida);

    RedeNeural *rede = cria_rede_neural(0.05, num_camadas, 2000, camadas);
    // print_matriz(rede->pesos_neuronio);

    print_matriz(rede->pesos_neuronio);
    // fit_rede_neural(rede, X_entrada, Y_saida);
    fit_rede_neural(rede, x, y);
    print_matriz(rede->pesos_neuronio);
    // predict_rede_neural(rede, X_entrada_test, Y_saida);
    predict_rede_neural(rede, x, y);
    print_matriz(y);

    return 0;
}
