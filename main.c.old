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
    float passo = 0.2;

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

    float W_linha_saida[2][4] = {
        { 0.2, 0.3, -0.1, -0.1},
        {-0.3, 0.4,  0.1,  0.2}
    };


    // float (*func_ptr[])(float) = {retificadora, leaky, tangente_hiperbolica, sigmoidal, sigmoidal};
    // float (*d_func_ptr[])(float) = {d_retificadora, d_leaky, d_tangente_hiperbolica, d_sigmoidal, d_sigmoidal};

    float (*func_ptr[])(float) = {retificadora, retificadora, retificadora, retificadora, retificadora};
    float (*d_func_ptr[])(float) = {d_retificadora, d_retificadora, d_retificadora, d_retificadora, d_retificadora};

    // entrada
    

    for (int epoca = 0; epoca < 1300; epoca++) {
        for (int rotulo = 0; rotulo < 5; rotulo++) {
            float integracao_interno[] = {0.0, 0.0, 0.0};
            float saida_camada[] = {0.0, 0.0, 0.0};
            float integracao_saida[] = {0.0, 0.0};
            float saida_rede[] = {0.0, 0.0};
        
            for (int a=0;a<3;a++) {
                integracao_interno[a] = 1 * W_interno[a][0];
                for (int i = 0; i < 2; i++) {
                    integracao_interno[a] += X_entradas[rotulo][i] * W_interno[a][1 + i];
                }
            }

            // for (int i=0;i<3;i++) {
            //     printf("%f ", integracao_interno[i]);
            // }
            // printf("\n");
            
            for (int i=0;i<3;i++) {
                saida_camada[i] = func_ptr[i](integracao_interno[i]);
            }

            // for (int i=0;i<3;i++) {
            //     printf("%f ", saida_camada[i]);
            // }
            // printf("\n");
            // entrada

            //saida

            for (int a=0;a<2;a++) {
                integracao_saida[a] = 1 * W_saida[a][0];
                for (int i = 0; i < 3; i++) {
                    integracao_saida[a] += saida_camada[i] * W_saida[a][1 + i];
                }
            }

            // for (int i=0;i<2;i++) {
            //     printf("%f ", integracao_saida[i]);
            // }
            // printf("\n");

            for (int i=0;i<2;i++) {
                saida_rede[i] = func_ptr[i+3](integracao_saida[i]);
            }

            // for (int i=0;i<2;i++) {
            //     printf("%f ", saida_rede[i]);
            // }
            // printf("\n");
            //saida

            //erro saida
            float erro[2] = {Y_entradas[rotulo][0] - saida_rede[0], Y_entradas[rotulo][1] - saida_rede[1]};

            // printf("erro = %f - %f\n", erro[0], erro[1]);
            //erro saida

            float delta[5] = {0, 0, 0, 0, 0};
            //delta saida
            
            delta[3] = d_func_ptr[3](integracao_saida[0]) * erro[0];
            delta[4] = d_func_ptr[4](integracao_saida[1]) * erro[1];

            //delta saida

            //novos peso saida
            for (int a=0;a<2;a++) {
                W_linha_saida[a][0] = W_saida[a][0] + passo * delta[a+3] * 1;
                for (int i = 0; i < 3; i++) {
                    W_linha_saida[a][i+1] = W_saida[a][i+1] + passo * delta[a+3] * saida_camada[i];
                }
            }
            //novos peso saida

            //novos delta entrada

            delta[0] = d_func_ptr[0](saida_camada[0]) * (W_saida[0][0+1] * delta[0+3] + W_saida[1][0+1] * delta[1+3]);
            delta[1] = d_func_ptr[1](saida_camada[1]) * (W_saida[0][1+1] * delta[0+3] + W_saida[1][1+1] * delta[1+3]);
            delta[2] = d_func_ptr[2](saida_camada[2]) * (W_saida[0][2+1] * delta[0+3] + W_saida[1][2+1] * delta[1+3]);

            //novos delta entrada

            //novos peso entrada
            for (int a=0;a<3;a++) {
                W_interno[a][0] = W_interno[a][0] + passo * delta[a] * 1;
                for (int i = 0; i < 2; i++) {
                    W_interno[a][i+1] = W_interno[a][i+1] + passo * delta[a] * saida_camada[i];
                }
            }

            //novos peso entrada
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    W_saida[i][j] = W_linha_saida[i][j];
                }
            }

        }
    }

    float entrada_predict[] = {0.0, 0.8};
    {
        float integracao_interno[] = {0.0, 0.0, 0.0};
        float saida_camada[] = {0.0, 0.0, 0.0};
        float integracao_saida[] = {0.0, 0.0};
        float saida_rede[] = {0.0, 0.0};
    
        for (int a=0;a<3;a++) {
            integracao_interno[a] = 1 * W_interno[a][0];
            for (int i = 0; i < 2; i++) {
                integracao_interno[a] += entrada_predict[i] * W_interno[a][1 + i];
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
        // entrada

        //saida

        for (int a=0;a<2;a++) {
            integracao_saida[a] = 1 * W_saida[a][0];
            for (int i = 0; i < 3; i++) {
                integracao_saida[a] += saida_camada[i] * W_saida[a][1 + i];
            }
        }

        for (int i=0;i<2;i++) {
            printf("%f ", integracao_saida[i]);
        }
        printf("\n");

        for (int i=0;i<2;i++) {
            saida_rede[i] = func_ptr[i+3](integracao_saida[i]);
        }

        for (int i=0;i<2;i++) {
            printf("respo = %f ", saida_rede[i]);
        }
        printf("\n");
        //saida
    }

    return 0;
}
