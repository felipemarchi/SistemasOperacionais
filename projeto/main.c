/**
 * Objetivo: Este programa deve buscar um valor numa matriz aleatória
 * utilizando múltiplas threads.
 * Autores: Brenda Alexsandra Januário;
 *          Felipe Carreiro Marchi;
 *          Pedro Henrique Bernini Silva.
 * Atualizado em: Seg 28 Mai 2018.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(){

    //Imprime cabeçalho
    header();

    //Variáveis do programa
    int potencia;
    int inteiro = 0;
    char validador;
    int i, valido;

    /* SEÇÃO 1 - GERA MATRIZ */
    printf("\n1. Para gerar a matriz, entre com...\n");

	//Trata entrada de linhas
        int m;
        char linhas[6];
        do{
            printf("\n\tNumero de linhas (M): ");
            fgets(linhas,6,stdin);	
	    potencia = strlen(linhas)-1;

            i = 0;
	    valido = 1;
            validador = linhas[i];
            do{
                if(!validaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = linhas[i];
            }while(validador!='\n');

            if(valido){
                linhas[i] = ' ';
	        m = inteiro;
            }else{
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
	    }
        }while(!valido);

	//Trata entrada de colunas
        int n;
        inteiro = 0;
        char colunas[6];
        do{
            printf("\n\tNumero de colunas (N): ");
            fgets(colunas,6,stdin);
	    potencia = strlen(colunas)-1;

            i = 0;
            valido = 1;
            validador = colunas[i];
            do{
                if(!validaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = colunas[i];
            }while(validador!='\n');

            if(valido){
                colunas[i] = ' ';
	        n = inteiro;
            }else{
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
	    }
        }while(!valido);

	//Recebe entrada do arquivo
        char nomeArquivo[30];
        printf("\n\tNome do arquivo: ");
	fgets(nomeArquivo,30,stdin);

	//Gera matriz m*n no arquivo
        printf("\n--------------------------------------------------------\n");
        geraMatriz(linhas,colunas,nomeArquivo);
        printf("--------------------------------------------------------\n");
    /**/

    /* SEÇÃO 2 - BUSCA VALOR */
    printf("\n2. Para buscar um valor na matriz, entre com...\n");

	//Trata entrada de threads
	int nThreads;
	printf("\n\tNumero de threads (T): ");
	scanf("%d",&nThreads);

	while(nThreads<=0 || nThreads>16 || nThreads>m*n){
	    printf("\tNumero invalido!\n");
	    printf("\tDigite novamente...\n");

	    printf("\n\tNumero de threads (T): ");
	    scanf("%d",&nThreads);
	}

	//Recebe entrada do valor de busca
	float valorBusca;
	printf("\n\tValor a ser buscado (V): ");
	scanf("%f",&valorBusca);

	//Busca valor na matriz
	printf("\n--------------------------------------------------------\n");
        printf("Buscando valores na matriz\n");
	printf("--------------------------------------------------------\n");
    /**/

    /* SEÇÃO 3 - IMPRIME RESULTADOS */
    if(!buscaValores(valorBusca,m,n,nThreads,nomeArquivo)){
        printf("\n3. Resultados...\n");
        imprimeResultados(inicio);
    }
    /**/

    return 0;
}
