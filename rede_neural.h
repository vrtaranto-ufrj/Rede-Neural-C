#pragma once

#include "matriz.h"

typedef struct RedeNeuralStruct RedeNeural;
typedef struct NeuronioStruct Neuronio;


struct NeuronioStruct {
    
};

struct RedeNeuralStruct {
    size_t num_entradas;
    size_t num_saidas;
    size_t num_camadas;
    size_t *num_neuronios_por_camada;

};


void cria_rede_neural(
    size_t num_entradas,
    size_t num_saidas,
    size_t num_camadas,
    size_t *num_neuronios_por_camada
);

void fit_rede_neural(RedeNeural *rede_neural, Matriz *entrada, Matriz *saida);

