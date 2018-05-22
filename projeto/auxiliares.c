#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "auxiliares.h"

void header(){
    printf("ESTE PROGRAMA DEVE BUSCAR UM\n");
    printf("VALOR NUMA MATRIZ ALEATORIA\n");
    printf("UTILIZANDO MULTIPLAS THREADS\n");
    printf("============================\n");
}

int retornaInt(char c, int *inteiro, int potencia){
    int numero = (c-48);
    potencia = --potencia;
    int multiplicador = pow(10,potencia);

    *inteiro += numero*multiplicador;

    if((int)c>=48 && (int)c<=57)
        return 1;
    else
        return 0;
}

void geraMatriz(char linhas[6], char colunas[6], char arquivo[30]){
    char comando[100] = "";
    arquivo[strlen(arquivo)-1] = '\0';

    strcat(comando,"../plugins/generateRandomMatrixDouble ");
    strcat(comando,linhas);
    strcat(comando,colunas);
    strcat(comando,"../arquivos/matrizes/");
    strcat(comando,arquivo);
    strcat(comando,".txt");

    system(comando);
}
