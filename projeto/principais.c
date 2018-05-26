#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "principais.h"

struct Argumentos{
    int inicio;
    int nLeituras;
    int nLinhas;
    int nColunas;
    char arquivo[30];
    float valorBusca;
};

typedef struct Lista_Resultados{
    int posicao[2];
    struct Lista_Resultados *prox;
}lista;
lista *inicio;

pthread_t threadID[16];
struct Argumentos vArgumentos[16];

int Inserir_fim_LS (lista **inicio, int linha, int coluna)
{
    lista *no_novo, *percorre;

    no_novo = (lista *) malloc(sizeof(lista));
    no_novo -> posicao[0] = linha;
    no_novo -> posicao[1] = coluna;
    no_novo -> prox = NULL;

    if(*inicio==NULL)
	    *inicio = no_novo;

	else{
	     percorre = *inicio;
	     while (percorre->prox != NULL)
	     {
	         percorre = percorre -> prox;
	     }
	    percorre->prox = no_novo;
	}
	return 0;
}

int inicializar(lista **inicio){
    *inicio = NULL;
    return 0;
}

void buscaValores(int nThreads,float valorBusca,int nLeituras,char arquivo[30],int m,int n){
    register int i;
    inicializar(&inicio);

    for(i=0; i<nThreads; i++){
	vArgumentos[i].nLinhas = m;
	vArgumentos[i].nColunas = n;
	vArgumentos[i].inicio = nLeituras*i;
	vArgumentos[i].nLeituras = nLeituras;
	vArgumentos[i].valorBusca = valorBusca;
	strcpy(vArgumentos[i].arquivo,arquivo);

	pthread_create(&threadID[i], NULL, threadBuscaValores, (void *)&vArgumentos[i]);
    }

    for(i=0; i<nThreads; i++){
        pthread_join(threadID[i], NULL);
    }
}

void *threadBuscaValores(void *vArgumentos){
    struct Argumentos *threadArgumentos = vArgumentos;
    int linha, coluna;
    float procura;
    int i;

    char caminho[100] = "";
    strcat(caminho,"../arquivos/matrizes/");
    strcat(caminho,threadArgumentos->arquivo);
    strcat(caminho,".txt");

    FILE *arquivo = fopen(caminho,"r");

    // Achando linha
    if(threadArgumentos->inicio%threadArgumentos->nColunas>0)
        linha = threadArgumentos->inicio/threadArgumentos->nColunas;
    else
        linha = threadArgumentos->inicio/threadArgumentos->nColunas - 1;

    // Achando coluna
    if(threadArgumentos->inicio%threadArgumentos->nColunas == 0)
        coluna = threadArgumentos->inicio%threadArgumentos->nColunas - 1;
    else
        coluna = threadArgumentos->inicio%threadArgumentos->nColunas;

    for(i=1;i<threadArgumentos->inicio;i++){
        fscanf(arquivo,"%f",&procura);
    }

    for(i=0;i<threadArgumentos->nLeituras;i++){
        fscanf(arquivo,"%f",&procura);
        if(procura == threadArgumentos->valorBusca){//Se encontrar o valorBusca
            Inserir_fim_LS (&inicio, linha, coluna);
        }

        if(coluna == threadArgumentos->nColunas){//Ir para a próxima posição
            coluna = 0;
            linha++;
        }else{
	    coluna++;
	}
    }

    pthread_exit(NULL);
}

int mostraResultados (lista *inicio)
{
    lista  *percorre;

    if (inicio==NULL)
	    printf("Nenhum valor encontrado\n");

	else {
	    percorre = inicio;
            printf("POSICAO ENCONTRADA: %d,%d\n",percorre->posicao[0], percorre->posicao[1]);
	     while (percorre->prox != NULL)
	     {
                 printf("POSICAO ENCONTRADA: %d,%d\n",percorre->posicao[0], percorre->posicao[1]);
	         percorre = percorre ->prox;
	     }
	}
	return 0;
}

int Obter_Tamanho_LS(lista *inicio, int *tam)
{
    lista *percorre;
    *tam = 0;
	if(inicio != NULL)
	{
       percorre = inicio;
	   while (percorre != NULL)
	   {
         (*tam)++;
         percorre = percorre -> prox;
	   }
     }
    else
    {
         *tam = 0;
    }
}


void ordenar_linha(lista **inicio)
{
    int tam;
    Obter_Tamanho_LS(*inicio,&tam);

    lista *anterior, *atual = (*inicio)->prox;

    for(int i=0; i<(tam-1); i++) {
        anterior = *inicio;
        for(int j=0; j<tam; j++) {
            if(anterior->posicao[0] > atual->posicao[0]) {
                //troca(anterior, atual);
            }
            atual = anterior->prox;
        }
        anterior = anterior->prox;
    }
}

void ordenar_coluna(lista **inicio)
{
    int tam;
    Obter_Tamanho_LS(*inicio,&tam);

    lista *anterior, *atual = (*inicio)->prox;

    for(int i=0; i<(tam-1); i++) {
        anterior = *inicio;
        for(int j=0; j<tam; j++) {
            if(anterior->posicao[1] > atual->posicao[1]) {
                //troca(anterior, atual);
            }
            atual = anterior->prox;
        }
        anterior = anterior->prox;
    }
}


