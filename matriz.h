#pragma once

#include <stdlib.h>

typedef struct MatrizStruct Matriz;

struct MatrizStruct {
    size_t linhas;
    size_t colunas;
    float *dados;
};

Matriz * inicializa_matriz(size_t linhas, size_t colunas);
void copiar_matriz(Matriz *matriz_origem, Matriz *matriz_destino);
Matriz * inicializa_matriz_copia(Matriz *matriz_origem);
void free_matriz(Matriz *matriz);

float get_elemento_matriz(Matriz *matriz, size_t i, size_t j);
float *get_ponteiro_elemento_matriz(Matriz *matriz, size_t i, size_t j);
void set_elemento_matriz(Matriz *matriz, size_t i, size_t j, float valor);
void set_matriz_zero(Matriz *matriz);

void print_matriz(Matriz *matriz);
void print_array(float *array, size_t size);
