#pragma once

#include <stdbool.h>

#include "matriz.h"

typedef struct RedeNeuralStruct RedeNeural;

struct RedeNeuralStruct {
    size_t num_entradas;
    size_t num_saidas;
    size_t num_camadas;

    size_t num_neuronios;

    size_t *camada_neuronios;  // {0, 0, 1, 1, 1, 2, 2}
    bool *is_bias;
    float (**funcoes_ativacao_neuronios)(float);
    float (**derivada_funcoes_ativacao_neuronios)(float);
    Matriz *pesos_neuronio;
};


float retificadora(float x);
float d_retificadora(float x);

RedeNeural* cria_rede_neural(
    size_t num_camadas,
    size_t *neuronios_por_camada  // {2, 3, 2}
);

void fit_rede_neural(RedeNeural *rede_neural, Matriz *X_entrada, Matriz *Y_saida);
void gerar_saida(
    RedeNeural *rede_neural,
    Matriz *X_entrada,
    float *integracao_neuronios,
    float *saida_neuronios
);
