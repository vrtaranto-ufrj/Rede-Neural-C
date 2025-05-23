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

    size_t *camada_neuronios;
    float (**funcoes_ativacao_neuronios)(float);
    Matriz pesos_neuronio;

};


void cria_rede_neural(
    size_t *camada_neuronios
);

void fit_rede_neural(RedeNeural *rede_neural, Matriz *entrada, Matriz *saida);

