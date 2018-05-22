#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(){

    header();

    char linhas[5];
    char colunas[5];
    char arquivo[30];
    float valorBusca;
    int nThreads;

    int m;
    int potencia;
    int inteiro = 0;
    char validador;
    int i, valido;

    printf("\n1. Para gerar a matriz, entre com...\n");

        do{
            i = 0;
            valido = 1;

            printf("\n\tNumero de linhas (M): ");
            fgets(linhas,5,stdin);	
	    potencia = strlen(linhas)-1;

            validador = linhas[i];
            do{
                if(!retornaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = linhas[i];
            }while(validador!='\n');

            if(!valido){
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
            }else{
                linhas[i] = ' ';
	        m = inteiro;
	    }
        }while(!valido);

        int n;
        inteiro = 0;
        do{
            i = 0;
            valido = 1;

            printf("\n\tNumero de colunas (N): ");
            fgets(colunas,5,stdin);
	    potencia = strlen(colunas)-1;

            validador = colunas[i];
            do{
                if(!retornaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = colunas[i];
            }while(validador!='\n');

            if(!valido){
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
            }else{
                colunas[i] = ' ';
	        n = inteiro;
	    }
        }while(!valido);

        printf("\n\tNome do arquivo: ");
	fgets(arquivo,30,stdin);

        printf("\n--------------------------------------------------------\n");
        geraMatriz(linhas,colunas,arquivo);
        printf("--------------------------------------------------------\n");

    printf("\n2. Para buscar um valor na matriz, entre com...\n");

	printf("\n\tNumero de threads (T): ");
	scanf("%d",&nThreads);

	while(nThreads<=0 || nThreads>16){
            printf("\tNumero invalido!\n");
            printf("\tDigite novamente...\n");

	    printf("\n\tNumero de threads (T): ");
	    scanf("%d",&nThreads);
	}

	printf("\n\tValor a ser buscado (V): ");
	scanf("%f",&valorBusca);

	int nLeituras = m*n/nThreads;

	printf("\n--------------------------------------------------------\n");
        printf("Buscando valores na matriz\n");
	printf("--------------------------------------------------------\n");

	buscaValores(nThreads,valorBusca,nLeituras,arquivo);

    return 0;
}
