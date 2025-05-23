#include <stdio.h>
#include <string.h>

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

void print_matriz(Matriz *matriz) {
    for (size_t i = 0; i < matriz->linhas; i++) {
        for (size_t j = 0; j < matriz->colunas; j++) {
            if (get_elemento_matriz(matriz, i, j) >= .0f) {
                printf(" ");
            }
            printf("%.2f  ", get_elemento_matriz(matriz, i, j));
        }
        printf("\n");
    }
}

void copiar_matriz(Matriz *matriz_origem, Matriz *matriz_destino) {
    if (matriz_destino->linhas != matriz_origem->linhas || matriz_destino->colunas != matriz_origem->colunas) {
        return;
    }
    for (size_t i = 0; i < matriz_origem->linhas; i++) {
        for (size_t j = 0; j < matriz_origem->colunas; j++) {
            set_elemento_matriz(matriz_destino, i, j, get_elemento_matriz(matriz_origem, i, j));
        }
    }
}

Matriz * inicializa_matriz_copiar(Matriz *matriz_origem) {
    Matriz *matriz_destino = inicializa_matriz(matriz_origem->linhas, matriz_origem->colunas);

    copiar_matriz(matriz_origem, matriz_destino);

    return matriz_destino;
}

void set_matriz_zero(Matriz *matriz) {
    memset(matriz->dados, 0, matriz->linhas * matriz->colunas);
}