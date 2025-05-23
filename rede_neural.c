#include "rede_neural.h"
#include "utils.h"

float retificadora(float x) {
    return x >= 0 ? x : 0;
}

float d_retificadora(float x) {
    return x >= 0 ? 1 : 0;
}

RedeNeural* cria_rede_neural(
    size_t num_camadas,
    size_t *neuronios_por_camada
) {
    if (num_camadas < 2) {
        return NULL;
    }

    RedeNeural *rede_neural = (RedeNeural *) malloc(sizeof(RedeNeural));
    if (rede_neural == NULL) {
        return NULL;
    }

    rede_neural->num_neuronios = sum_unsigned_long(neuronios_por_camada, num_camadas) + num_camadas - 1;

    rede_neural->camada_neuronios = (size_t *) malloc(sizeof(size_t) * rede_neural->num_neuronios);
    if (rede_neural->camada_neuronios == NULL) {
        free(rede_neural);
        return NULL;
    }

    size_t posicao_atual = 0, neuronios_camada;
    for (size_t i = 0; i < num_camadas; i++) {
        neuronios_camada = neuronios_por_camada[i];
        if (i != num_camadas - 1) {
            neuronios_camada++;
        }

        size_t final_camada = posicao_atual + neuronios_camada;
        for (size_t j = posicao_atual; j < final_camada; j++) {
            rede_neural->camada_neuronios[j] = i;
            posicao_atual++;
        }
    }

    rede_neural->num_entradas = neuronios_por_camada[0];
    rede_neural->num_saidas = neuronios_por_camada[num_camadas - 1];

    rede_neural->funcoes_ativacao_neuronios = (float(**)(float)) malloc(sizeof(float(*)(float)) * rede_neural->num_neuronios);
    if (rede_neural->funcoes_ativacao_neuronios == NULL) {
        free(rede_neural->camada_neuronios);
        free(rede_neural);
        return NULL;
    }
    rede_neural->derivada_funcoes_ativacao_neuronios = (float(**)(float)) malloc(sizeof(float(*)(float)) * rede_neural->num_neuronios);
    if (rede_neural->derivada_funcoes_ativacao_neuronios == NULL) {
        free(rede_neural->funcoes_ativacao_neuronios);
        free(rede_neural->camada_neuronios);
        free(rede_neural);
        return NULL;
    }

    for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
        rede_neural->funcoes_ativacao_neuronios[i] = retificadora;
        rede_neural->funcoes_ativacao_neuronios[i] = d_retificadora;    
    }

    rede_neural->pesos_neuronio = inicializa_matriz(rede_neural->num_neuronios, rede_neural->num_neuronios);

    size_t inicio_j = 0;
    for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
        for (size_t j = ++inicio_j; j < rede_neural->num_neuronios; j++) {
            if (rede_neural->camada_neuronios[i] + 1 == rede_neural->camada_neuronios[j]) {
                set_elemento_matriz(rede_neural->pesos_neuronio, i, j, (float) rand());  // arrumar o rand
            }
        }
    }
    
    return rede_neural;
}