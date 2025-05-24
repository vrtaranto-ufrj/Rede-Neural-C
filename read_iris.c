#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
    Matriz **X_entrada,
    Matriz **Y_saida
) {
    FILE *arquivo_iris = fopen(nome_arquivo, "r");
    char buffer[BUFFER_SIZE] = {0};
    char *final, *inicio;
    int coluna;

    *X_entrada = inicializa_matriz(NUM_ROTULOS, NUM_ENTRADAS);
    *Y_saida = inicializa_matriz(NUM_ROTULOS, NUM_IRIS);
    
    for (int linha = 0; linha < NUM_ROTULOS; linha++) {
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
