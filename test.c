#include <stdio.h>

#include "rede_neural.h"

int main(int argc, char const *argv[]) {
    size_t camadas[] = {2UL, 3UL, 2UL};
    RedeNeural *rede = cria_rede_neural(3, camadas);
    printf("%p\n", rede);

    printf("%lu, %lu, %lu\n", rede->num_entradas, rede->num_saidas, rede->num_neuronios);

    print_matriz(rede->pesos_neuronio);

    return 0;
}
