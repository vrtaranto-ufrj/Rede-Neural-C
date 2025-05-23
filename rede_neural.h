#pragma once

#include "matriz.h"

typedef struct RedeNeuralStruct RedeNeural;
typedef struct NeuronioStruct Neuronio;


struct NeuronioStruct {
    float (*funcao_ativacao)(float);

};

struct RedeNeuralStruct {
    size_t num_entradas;
    size_t num_saidas;

    size_t num_neuronios;

    size_t *camada_neuronios;  // {0, 0, 1, 1, 1, 2, 2}
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

void fit_rede_neural(RedeNeural *rede_neural, Matriz *entrada, Matriz *saida);
