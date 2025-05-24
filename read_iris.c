#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "read_iris.h"

const char const *iris_types[] = {
    "Iris-setosa",
    "Iris-versicolor",
    "Iris-virginica"
};

int idx_iris_saida(const char const *iris) {
    for (int idx = 0; idx < NUM_IRIS; idx++) {
        if (!strcmp(iris, iris_types[idx])) {
            return idx;
        }
    }
}

void preenche_matrizes_iris(
    const char const *nome_arquivo,
    int num_rotulos,
    Matriz **X_entrada,
    Matriz **Y_saida
) {
    FILE *arquivo_iris = fopen(nome_arquivo, "r");
    char buffer[BUFFER_SIZE] = {0};
    char *final, *inicio;
    int coluna;

    *X_entrada = inicializa_matriz(num_rotulos, NUM_ENTRADAS);
    *Y_saida = inicializa_matriz(num_rotulos, NUM_IRIS);
    
    for (int linha = 0; linha < num_rotulos; linha++) {
        coluna = 0;
        fgets(buffer, BUFFER_SIZE, arquivo_iris);
        buffer[strcspn(buffer, "\n")] = '\0';
        inicio = buffer;
        for (int virgula_atual = 0; virgula_atual <= NUM_ENTRADAS; virgula_atual++) {
            final = strchr(inicio, ',');
            if (final != NULL) {
                *final = '\0';
            }
            
            if (coluna < NUM_ENTRADAS) {  // Entradas
                set_elemento_matriz(
                    *X_entrada,
                    linha,
                    coluna++,
                    strtof(inicio, NULL)
                );
            } else {  // Saida
                set_elemento_matriz(
                    *Y_saida,
                    linha,
                    idx_iris_saida(inicio),
                    1
                );
            }
            inicio = final + 1;

        }
    }

}

float calcular_acuracia(Matriz *ground_truth, Matriz *resposta_rede) {
    float acuracia = 0, acertou;
    int maior_truth, maior_resp;
    float maior_truth_v, maior_resp_v;

    for (int i = 0; i < ground_truth->linhas; i++) {
        maior_truth = -1;
        maior_resp = -1;
        maior_truth_v = 0;
        maior_resp_v = 0;

        for (int j = 0; j < ground_truth->colunas; j++) {
            if (get_elemento_matriz(resposta_rede, i, j) > maior_resp_v) {
                maior_resp_v = get_elemento_matriz(resposta_rede, i, j);
                maior_resp = j;
            } if (get_elemento_matriz(ground_truth, i, j) > maior_truth_v) {
                maior_truth_v = get_elemento_matriz(ground_truth, i, j);
                maior_truth = j;
            }
        }
        acuracia += maior_resp == maior_truth; 
    }

    return acuracia / ground_truth->linhas;
}