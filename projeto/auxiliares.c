#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "auxiliares.h"

/**
 * Função auxiliar que imprime cabeçalho do programa
**/
void header(){
    printf("ESTE PROGRAMA DEVE BUSCAR UM\n");
    printf("VALOR NUMA MATRIZ ALEATORIA\n");
    printf("UTILIZANDO MULTIPLAS THREADS\n");
    printf("============================\n");
}

/**
 * Função auxiliar que valida se um char é um número inteiro
 * retornando também o próprio inteiro por referência
 *
 * @param c - caractere a ser validado
 * @param *inteiro - ponteiro para ter o inteiro por referência
 * @param potencia - valor auxiliar para calcular o inteiro
 *
 * @return 1 - char é um número inteiro
 * @return 0 - char não é um número inteiro 
**/
int validaInt(char c, int *inteiro, int potencia){
    if((int)c>=48 && (int)c<=57){
        int numero = (c-48);
        potencia = --potencia;
        int multiplicador = pow(10,potencia);

        *inteiro += numero*multiplicador;

        return 1;
    }else
        return 0;
}

/**
 * Função auxiliar que executa outro programa do projeto
 * para gerar uma matriz em um arquivo
 *
 * @param linhas - número de linhas da matriz
 * @param colunas - número de colunas da matriz
 * @param arquivo - nome do arquivo a ser gravado
 *
 * Observações: programa auxiliar desenvolvido
 * pelo Professor Andre Leon S. Gradvohl, Dr.
**/
void geraMatriz(char linhas[6], char colunas[6], char arquivo[30]){
    arquivo[strlen(arquivo)-1] = '\0';
    char comando[100] = "";

    strcat(comando,"../plugins/generateRandomMatrixDouble ");
    strcat(comando,linhas);
    strcat(comando,colunas);
    strcat(comando,"../arquivos/matrizes/");
    strcat(comando,arquivo);
    strcat(comando,".txt");

    system(comando);
}
