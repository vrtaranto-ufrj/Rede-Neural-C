#pragma once

#include "matriz.h"

#define NUM_ENTRADAS 4
#define BUFFER_SIZE 1024
#define NUM_IRIS 3  // 3 classes "Iris-setosa", "Iris-versicolor", "Iris-virginica"

int idx_iris_saida(const char const *iris);

void preenche_matrizes_iris(
    const char const *nome_arquivo,
    int num_rotulos,
    Matriz **X_entrada,
    Matriz **Y_saida
);

float calcular_acuracia(Matriz *ground_truth, Matriz *resposta_rede);
