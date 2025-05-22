#include <stdio.h>

#include "matriz.h"

int main(int argc, char const *argv[]) {
    Matriz *matriz = inicializa_matriz(5, 2);    

    free_matriz(matriz);
    return 0;
}
