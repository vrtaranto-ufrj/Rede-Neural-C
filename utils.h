#pragma once

#include <stdlib.h>

float max(float *array, size_t size) {
    if (size == 0) {
        return 0;
    }

    size_t maior = array[0];

    if (size == 1) {
        return maior;
    }

    for (size_t i = 1; i < size; i++) {
        if (array[i] > maior) {
            maior = array[i];
        }
    }

    return maior;
}

float sum_float(float *array, size_t size) {
    if (size == 0) {
        return 0;
    }
    float soma = 0;

    for (size_t i = 0; i < size; i++) {
        soma += array[i];
    }

    return soma;
}

int sum_int(int *array, size_t size) {
    if (size == 0) {
        return 0;
    }
    int soma = 0;

    for (size_t i = 0; i < size; i++) {
        soma += array[i];
    }

    return soma;
}

unsigned long sum_unsigned_long(unsigned long *array, size_t size) {
    if (size == 0) {
        return 0;
    }
    int soma = 0;

    for (size_t i = 0; i < size; i++) {
        soma += array[i];
    }

    return soma;
}