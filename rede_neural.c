#include <string.h>
#include <math.h>

#include "rede_neural.h"
#include "utils.h"

float retificadora(float x) {
    return x >= 0 ? x : 0;
}

float d_retificadora(float x) {
    return x >= 0 ? 1 : 0;
}

float sigmoidal(float x) {
    float a = 5;
    return 1 / (1 + expf(- a * x));
}

float d_sigmoidal(float x) {
    float a = 5;
    float resp_sigmoidal = sigmoidal(x);
    return a * resp_sigmoidal * (1 - resp_sigmoidal);
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

void inicializa_pesos_HE(RedeNeural *rede_neural) {
    rede_neural->pesos_neuronio = inicializa_matriz(rede_neural->num_neuronios, rede_neural->num_neuronios);

    size_t inicio_j = 0;
    for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
        // Count incoming connections to calculate scaling factor
        size_t fan_in = 0;
        for (size_t k = 0; k < rede_neural->num_neuronios; k++) {
            if (!rede_neural->is_bias[k] && 
                rede_neural->camada_neuronios[k] + 1 == rede_neural->camada_neuronios[i]) {
                fan_in++;
            }
        }
        
        // Use at least 1 to avoid division by zero
        fan_in = fan_in > 0 ? fan_in : 1;
        
        // He initialization scale factor
        float scale = sqrtf(2.0f / fan_in);
        
        for (size_t j = inicio_j++; j < rede_neural->num_neuronios; j++) {
            if (!rede_neural->is_bias[j] &&
                rede_neural->camada_neuronios[i] + 1 == rede_neural->camada_neuronios[j]) {
                // He initialization (uniform variant)
                float rand_val = (float)rand() / (float)RAND_MAX;  // [0,1]
                float weight = (rand_val * 2.0f - 1.0f) * scale;   // [-scale,scale]
                set_elemento_matriz(rede_neural->pesos_neuronio, i, j, weight);
            }
        }
    }
}

RedeNeural* cria_rede_neural(
    float passo,
    size_t num_camadas,
    size_t num_epocas,
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
    rede_neural->passo = passo;
    rede_neural->num_epocas = num_epocas;

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
        rede_neural->derivada_funcoes_ativacao_neuronios[i] = d_retificadora;    
    }
    
    inicializa_pesos_HE(rede_neural);

    return rede_neural;
}

void fit_rede_neural(RedeNeural *rede_neural, Matriz *X_entrada, Matriz *Y_saida) {
    float *integracao, *saida, *delta;
    Matriz *pesos_temp;
    
    integracao = malloc(sizeof(float) * rede_neural->num_neuronios);
    saida = malloc(sizeof(float) * rede_neural->num_neuronios);
    delta = calloc(sizeof(float), rede_neural->num_neuronios);
    pesos_temp = inicializa_matriz(
        rede_neural->pesos_neuronio->linhas,
        rede_neural->pesos_neuronio->colunas
    );

    for (size_t epoca = 0; epoca < rede_neural->num_epocas; epoca++) {
        // print_matriz(pesos_temp);
        for (size_t rotulo = 0; rotulo < X_entrada->linhas; rotulo++) {
            gerar_saida(
                rede_neural,
                X_entrada,
                integracao,
                saida,
                rotulo
            );

            size_t neuronio_atual = rede_neural->num_neuronios;
            float erro;
            do {
                neuronio_atual--;

                if (neuronio_atual >= rede_neural->num_neuronios - rede_neural->num_saidas) {
                    erro = get_elemento_matriz(Y_saida, rotulo, rede_neural->num_neuronios - neuronio_atual - 1) - saida[neuronio_atual];
                } else {
                    erro = 0;
                    for (size_t vizinho = 0; vizinho < rede_neural->num_neuronios; vizinho++) {
                        if (
                            rede_neural->camada_neuronios[vizinho] == rede_neural->camada_neuronios[neuronio_atual] + 1
                            &&
                            !rede_neural->is_bias[vizinho]
                        ){
                        erro += get_elemento_matriz(rede_neural->pesos_neuronio, neuronio_atual, vizinho) * delta[vizinho];
                        }
                    }
                }
                delta[neuronio_atual] = rede_neural->derivada_funcoes_ativacao_neuronios[neuronio_atual](integracao[neuronio_atual]) * erro;

                for (size_t aresta = 0; aresta < rede_neural->num_neuronios; aresta++) {
                    if (
                        rede_neural->camada_neuronios[aresta] == rede_neural->camada_neuronios[neuronio_atual] - 1
                        &&
                        !rede_neural->is_bias[neuronio_atual]
                    ) {
                        set_elemento_matriz(
                            pesos_temp,
                            aresta,
                            neuronio_atual,
                            get_elemento_matriz(
                                rede_neural->pesos_neuronio,
                                aresta,
                                neuronio_atual
                            ) + rede_neural->passo * delta[neuronio_atual] * saida[aresta]
                        );
                    }
                }

            } while (neuronio_atual);
            copiar_matriz(pesos_temp, rede_neural->pesos_neuronio);
        }
    }

    free(integracao);
    free(saida);
}

void predict_rede_neural(RedeNeural *rede_neural, Matriz *X_entrada, Matriz *Y_saida) {
    float *integracao, *saida;
    
    integracao = malloc(sizeof(float) * rede_neural->num_neuronios);
    saida = malloc(sizeof(float) * rede_neural->num_neuronios);

    for (size_t rotulo = 0; rotulo < X_entrada->linhas; rotulo++) {
        gerar_saida(rede_neural, X_entrada, integracao, saida, rotulo);

        for (size_t i = 0; i < rede_neural->num_saidas; i++) {
            size_t idx = rede_neural->num_neuronios - rede_neural->num_saidas + (rede_neural->num_saidas - i - 1);
            set_elemento_matriz(Y_saida, rotulo, i, saida[idx]);
        }
    }

    free(integracao);
    free(saida);
}

void gerar_saida(
    RedeNeural *rede_neural,
    Matriz *X_entrada,
    float *integracao_neuronios,
    float *saida_neuronios,
    size_t rotulo
) {
    memset(integracao_neuronios, 0, rede_neural->num_neuronios * sizeof(float));
    memset(saida_neuronios, 0, rede_neural->num_neuronios * sizeof(float));

    saida_neuronios[0] = 1;
    for (size_t i = 1; i < rede_neural->num_neuronios; i++) {
        if (rede_neural->is_bias[i]) {
            saida_neuronios[i] = 1;
        }
        else if (rede_neural->camada_neuronios[i] == 0) {
            saida_neuronios[i] = get_elemento_matriz(X_entrada, rotulo, i - 1);
        }
    }

    for (size_t camada = 1; camada < rede_neural->num_camadas; camada++) {

        for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
            if (rede_neural->camada_neuronios[i] == camada && !rede_neural->is_bias[i]) {  // Tirando os bias pra agilzar
                for (size_t aresta = 0; aresta < rede_neural->num_neuronios; aresta++) {
                    integracao_neuronios[i] += saida_neuronios[aresta] * get_elemento_matriz(rede_neural->pesos_neuronio, aresta, i);
                }
            }
        }

        for (size_t i = 0; i < rede_neural->num_neuronios; i++) {
            if (rede_neural->camada_neuronios[i] == camada && !rede_neural->is_bias[i]) {
                saida_neuronios[i] = rede_neural->funcoes_ativacao_neuronios[i](integracao_neuronios[i]);
            }
        }
    }
}