#pragma once

#include "matriz.h"

#define NUM_ROTULOS 150
#define NUM_ENTRADAS 4
#define BUFFER_SIZE 40
#define NUM_IRIS 3  // 3 classes "Iris-setosa", "Iris-versicolor", "Iris-virginica"

int idx_iris_saida(const char const *iris);

void preenche_matrizes_iris(
    const char const *nome_arquivo,
    Matriz **X_entrada,
    Matriz **Y_saida
);
