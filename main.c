#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float retificadora(float x) {
    return x >= 0 ? x : 0;
}

float d_retificadora(float x) {
    return x >= 0 ? 1 : 0;
}

float leaky(float x) {
    float a = 0.2;
    return x >= 0 ? x : a * x;
}

float d_leaky(float x) {
    float a = 0.2;
    return x >= 0 ? 1 : a;
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

float tangente_hiperbolica(float x) {
    return tanhf(x);
}

float d_tangente_hiperbolica(float x) {
    float resp_tanh = tanhf(x);
    return 1 - resp_tanh * resp_tanh;
}


int main(int argc, char const *argv[]) {
    float X_entradas[5][2] = {
        {0.8, 0.7},
        {0.1, 0.1},
        {0.2, 0.6},
        {0.9, 0.2},
        {0.0, 0.8}
    };

    float Y_entradas[5][2] = {
        {0.70, 0.50},
        {0.21, 0.29},
        {0.32, 0.81},
        {0.38, 0.02},
        {0.20, 0.50}
    };

    float W_interno[3][3] = {
        { 0.3, 0.1, 0.0},
        {-0.2, 0.3, 0.1},
        {-0.1, 0.0, 0.2}
    };

    float W_saida[2][4] = {
        { 0.2, 0.3, -0.1, -0.1},
        {-0.3, 0.4,  0.1,  0.2}
    };


    float (*func_ptr[])(float) = {retificadora, leaky, tangente_hiperbolica, sigmoidal, sigmoidal};
    float (*d_ptr[])(float) = {d_retificadora, d_leaky, d_tangente_hiperbolica, d_sigmoidal, d_sigmoidal};

    float integracao_interno[] = {0.0, 0.0, 0.0};
    float saida_camada[] = {0.0, 0.0, 0.0};
    
    for (int a=0;a<3;a++) {
        integracao_interno[a] = 1 * W_interno[a][0];
        for (int i = 0; i < 2; i++) {
            integracao_interno[a] += X_entradas[0][i] * W_interno[a][1 + i];
        }
    }

    for (int i=0;i<3;i++) {
        printf("%f ", integracao_interno[i]);
    }
    printf("\n");
    
    for (int i=0;i<3;i++) {
        saida_camada[i] = func_ptr[i](integracao_interno[i]);
    }

    for (int i=0;i<3;i++) {
        printf("%f ", saida_camada[i]);
    }
    printf("\n");



    return 0;
}
