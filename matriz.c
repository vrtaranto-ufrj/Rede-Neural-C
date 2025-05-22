#include "matriz.h"

Matriz * inicializa_matriz(size_t linhas, size_t colunas) {
    Matriz *matriz = (Matriz *) calloc(1, sizeof(Matriz));
    if (matriz == NULL) {
        return NULL;
    }

    matriz->dados = (float *) calloc(linhas * colunas, sizeof(float));
    if (matriz->dados == NULL) {
        return NULL;
    }

    matriz->linhas = linhas;
    matriz->colunas = colunas;
    return matriz;
}

void free_matriz(Matriz *matriz) {
    free(matriz->dados);
    free(matriz);
}

float get_elemento_matriz(Matriz *matriz, size_t i, size_t j) {
    // if (i >= matriz->linhas || j >= matriz->colunas) {
    //     return 0;
    // }

    return matriz->dados[i + j*matriz->colunas];
}

void set_elemento_matriz(Matriz *matriz, size_t i, size_t j, float valor) {
    // if (i >= matriz->linhas || j >= matriz->colunas) {
    //     return;
    // }
    matriz->dados[i + j*matriz->colunas] = valor;
}
