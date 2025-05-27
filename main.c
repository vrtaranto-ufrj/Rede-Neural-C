#include <stdio.h>

#include "rede_neural.h"
#include "read_iris.h"

int main(int argc, char const *argv[]) {
    Matriz *x, *y, *x_test, *y_test, *y_resposta;

    preenche_matrizes_iris("iris_train.data", 120, &x, &y);
    preenche_matrizes_iris("iris_test.data", 30, &x_test, &y_test);
    y_resposta = inicializa_matriz_copia(y_test);


    size_t camadas[] = {4, 2, 3};
    size_t num_camadas = sizeof(camadas) / sizeof(size_t);

    RedeNeural *rede = cria_rede_neural(0.02, num_camadas, 10000, camadas);
    print_matriz(rede->pesos_neuronio);

    fit_rede_neural(rede, x, y);
    print_matriz(rede->pesos_neuronio);

    predict_rede_neural(rede, x_test, y_resposta);
    print_matriz(y_test);
    print_matriz(y_resposta);

    printf("Acuracia = %f\n", calcular_acuracia(y_test, y_resposta));

    return 0;
}
