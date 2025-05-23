#include <string.h>

#include "rede_neural.h"
#include "utils.h"

float retificadora(float x) {
    return x >= 0 ? x : 0;
}

float d_retificadora(float x) {
    return x >= 0 ? 1 : 0;
}

void inicializa_pesos_random(RedeNeural *rede_neural) {
    rede_neural->pesos_neuronio = inicializa_matriz(rede_neural->num_neuronios, rede_neural->num_neuronios);

    size_t inicio_j = 0;
    for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
        for (size_t j = inicio_j++; j < rede_neural->num_neuronios; j++) {
            if (
                !rede_neural->is_bias[j] &&
                rede_neural->camada_neuronios[i] + 1 == rede_neural->camada_neuronios[j]
            ) {
                set_elemento_matriz(rede_neural->pesos_neuronio, i, j, (float) rand() / (float) RAND_MAX * 2.0f - 1.0f);  // arrumar o rand
            }
        }
    }
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

    rede_neural->is_bias = (bool *) calloc(sizeof(bool), rede_neural->num_neuronios);
    if (rede_neural->is_bias == NULL) {
        free(rede_neural->camada_neuronios);
        free(rede_neural);
        return NULL;
    }

    size_t posicao_atual = 0, neuronios_camada;
    for (size_t i = 0; i < num_camadas; i++) {
        neuronios_camada = neuronios_por_camada[i];
        if (i != num_camadas - 1) {
            neuronios_camada++;
        }

        size_t final_camada = posicao_atual + neuronios_camada, posicao_inicial = posicao_atual;
        for (size_t j = posicao_inicial; j < final_camada; j++) {
            if (j == posicao_inicial && i != num_camadas - 1) {
                rede_neural->is_bias[j] = true;
            }
            rede_neural->camada_neuronios[j] = i;
            posicao_atual++;
        }
    }

    rede_neural->num_entradas = neuronios_por_camada[0];
    rede_neural->num_saidas = neuronios_por_camada[num_camadas - 1];
    rede_neural->num_camadas = num_camadas;

    rede_neural->funcoes_ativacao_neuronios = (float(**)(float)) malloc(sizeof(float(*)(float)) * rede_neural->num_neuronios);
    if (rede_neural->funcoes_ativacao_neuronios == NULL) {
        free(rede_neural->camada_neuronios);
        free(rede_neural->is_bias);
        free(rede_neural);
        return NULL;
    }

    rede_neural->derivada_funcoes_ativacao_neuronios = (float(**)(float)) malloc(sizeof(float(*)(float)) * rede_neural->num_neuronios);
    if (rede_neural->derivada_funcoes_ativacao_neuronios == NULL) {
        free(rede_neural->funcoes_ativacao_neuronios);
        free(rede_neural->is_bias);
        free(rede_neural->camada_neuronios);
        free(rede_neural);
        return NULL;
    }

    for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
        rede_neural->funcoes_ativacao_neuronios[i] = retificadora;
        rede_neural->funcoes_ativacao_neuronios[i] = d_retificadora;    
    }
    
    inicializa_pesos_random(rede_neural);

    return rede_neural;
}

void gerar_saida(
    RedeNeural *rede_neural,
    Matriz *X_entrada,
    float *integracao_neuronios,
    float *saida_neuronios
) {
    for (size_t rotulo = 0; rotulo < X_entrada->linhas; rotulo++) {
        memset(integracao_neuronios, 0, rede_neural->num_neuronios);
        memset(saida_neuronios, 0, rede_neural->num_neuronios);

        saida_neuronios[0] = 1;
        for (size_t neuronio_entrada = 1; neuronio_entrada <= rede_neural->num_entradas; neuronio_entrada++) {
            saida_neuronios[neuronio_entrada] = get_elemento_matriz(X_entrada, rotulo, neuronio_entrada - 1);
        }

        for (size_t camada = 1; camada < rede_neural->num_camadas; camada++) {

            for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
                if (rede_neural->camada_neuronios[i] == camada && !rede_neural->is_bias[i]) {
                    for (size_t aresta = 0; aresta < rede_neural->num_neuronios; aresta++) {
                        integracao_neuronios[i] += saida_neuronios[aresta] * get_elemento_matriz(rede_neural->pesos_neuronio, aresta, i);
                    }
                }
            }   
        }
    }
}