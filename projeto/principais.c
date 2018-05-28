#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "principais.h"

//Vari�veis globais do programa
lista *inicio;
pthread_t threadID[16];
argumentos vArgumentos[16];

/**
 * Fun��o que cria threads passando os argumentos necess�rios para busca
 * tamb�m pede ao programa esperar as threads terminarem
 *
 * @param valorBusca - valor a ser buscado na matriz
 * @param m - n�mero de linhas da matriz
 * @param n - n�mero de colunas da matriz
 * @param nThreads - n�mero de theads para executar
 * @param nomeArquivo - nome do arquivo da matriz
 *
 * @return 0 - Sucesso
 * @return 1 - Erro ao inicializar lista 
**/
int buscaValores(float valorBusca,int m,int n,int nThreads,char nomeArquivo[30]){
    //Fun��o depende da iniciliza��o da lista
    if(!inicializarLista(&inicio)){

        register int i;
        int nLeituras = m*n/nThreads;

        //Cria threads passando argumentos necess�rios
        for(i=0; i<nThreads; i++){
	    vArgumentos[i].idThread = i + 1;
	    vArgumentos[i].nLinhas = m;
	    vArgumentos[i].nColunas = n;
	    vArgumentos[i].nThreads = nThreads;
	    vArgumentos[i].nLeituras = nLeituras;
	    vArgumentos[i].valorBusca = valorBusca;
	    vArgumentos[i].posicaoInicial = nLeituras*i + 1;
	    strcpy(vArgumentos[i].nomeArquivo,nomeArquivo);

	    pthread_create(&threadID[i], NULL, threadBuscaValores, (void *)&vArgumentos[i]);
        }

        //Faz com que a main() n�o termine antes
        for(i=0; i<nThreads; i++)
            pthread_join(threadID[i], NULL);

    }else{
        printf("\nNao foi possivel inicializar a lista!\n");
	return 1;
    }
    return 0;
}

/**
 * Fun��o que representa uma thread gen�rica que deve percorrer
 * o arquivo a partir de um ponto em busca do valorBusca
 *
 * @param *vArgumentos - ponteiro para uma estrutura de argumentos
**/
void *threadBuscaValores(void *vArgumentos){
    argumentos *argumentos = vArgumentos;

    //Abre arquivo da matriz
    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,argumentos->nomeArquivo);
    strcat(diretorio,".txt");
    FILE *arquivo = fopen(diretorio,"r");

    //Calcula �ndice linha segundo posi��o inicial
    int linha;
    if(argumentos->posicaoInicial%argumentos->nColunas > 0 || argumentos->posicaoInicial/argumentos->nColunas == 0)
        linha = argumentos->posicaoInicial/argumentos->nColunas;
    else
        linha = argumentos->posicaoInicial/argumentos->nColunas - 1;

    //Calcula �ndice coluna segundo posi��o inicial
    int coluna;
    if(argumentos->posicaoInicial-argumentos->nColunas < 0)
        coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas + argumentos->nColunas;
    else if((argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas == 0)
        coluna = argumentos->nColunas;
    else
	coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas;
    coluna--;

    //Percorre matriz at� a posi��o inicial
    float procura;
    register int i;
    argumentos->posicaoInicial--;
    for(i=1;i<=argumentos->posicaoInicial;i++){
        fscanf(arquivo,"%f",&procura);
    }

    //L� e compara nLeitura vezes
    if(argumentos->idThread != argumentos->nThreads){
	int j;
	for(j=0;j<argumentos->nLeituras;j++){
	    fscanf(arquivo,"%f",&procura);
	    if(procura == argumentos->valorBusca)
	        insereListaFim(&inicio, linha, coluna);

	    if(coluna == argumentos->nColunas-1){
	        coluna = 0;
	        linha++;
	    }else
	        coluna++;
	}
    //Ou at� o final do arquivo, se for o caso
    }else{
	do{
	    fscanf(arquivo,"%f",&procura);
	    if(procura == argumentos->valorBusca && linha != argumentos->nLinhas)
	        insereListaFim(&inicio, linha, coluna);
	    
	    if(coluna == argumentos->nColunas-1){
	        coluna = 0;
	        linha++;
	    }else
	        coluna++; 
	}while(!feof(arquivo));
    }

    //Finaliza thread
    pthread_exit(NULL);
}

/**
 * Fun��o que imprime posi��es ordenadas da matriz
 * onde o valor buscado se encontra
 *
 * @param *inicio - lista encadeada a ser impressa
**/
void imprimeResultados(lista *inicio){
    lista *percorre;

    //N�o existe valores na lista
    if (inicio==NULL)
	printf("\n\tO valor buscado nao pertence a matriz");

    //Existe valores na lista
    else{

        ordenarLista(&inicio);

	percorre = inicio;
	printf("\n\tO valor buscado encontra-se na matriz nas posicoes:\n");
	printf("\n\t(%d,%d)",percorre->posicao[0],percorre->posicao[1]);
        while(percorre->prox != NULL){
	    percorre = percorre->prox;
	    printf("\n\t(%d,%d)",percorre->posicao[0],percorre->posicao[1]);
        }
    }
    printf("\n");
}

//FUN��ES DE MANIPULA��O DA LISTA

/**
 * Fun��o que inicializa lista encadeada
 *
 * @param **inicio = endere�o de mem�ria da lista a ser inicializada
 *
 * @return 0 - Sucesso
**/
int inicializarLista(lista **inicio){
    *inicio = NULL;
    return 0;
}

/**
 * Fun��o que insere a posi��o encontrada no fim da lista encadeada
 *
 * @param **inicio = endere�o de mem�ria da lista a ser inserida
 * @param linha = �ndice da linha da matriz na posi��o do elemento encontrado
 * @param coluna = �ndice da coluna da matriz na posi��o do elemento encontrado
**/
void insereListaFim(lista **inicio, int linha, int coluna){
    lista *no_novo, *percorre;

    no_novo = (lista *) malloc(sizeof(lista));

    no_novo->posicao[0] = linha;
    no_novo->posicao[1] = coluna;
    no_novo->prox = NULL;

    if(*inicio==NULL)
        *inicio = no_novo;
    else{
	percorre = *inicio;
	while (percorre->prox != NULL)
	    percorre = percorre->prox;
	percorre->prox = no_novo;
    }
}

/**
 * Fun��o que ordena posi��es da lista
 *
 * @param **inicio - endere�o de mem�ria da lista a ser ordenada
**/
void ordenarLista(lista **inicio){
    lista *anterior;
    lista *atual;
    int temp[2];

    //Ordena posicao[0] referente a linha da matriz
    anterior = *inicio;

    while(anterior->prox != NULL){
    	atual = anterior->prox;
        while(atual != NULL){
            if(anterior->posicao[0] > atual->posicao[0]){
                temp[0] = atual->posicao[0];
                temp[1] = atual->posicao[1];
                atual->posicao[0] = anterior->posicao[0];
                atual->posicao[1] = anterior->posicao[1];
                anterior->posicao[0] = temp[0];
                anterior->posicao[1] = temp[1];
            }
            atual = atual->prox;
        }
        anterior = anterior->prox;
    }

    //Ordena posicao[1] referente a coluna da matriz,
    //por�m agrupando por linhas j� ordenadas
    anterior = *inicio;

    while(anterior->prox != NULL){
    	atual = anterior->prox;
	while(atual != NULL && anterior->posicao[0] == atual->posicao[0]){
	    if(anterior->posicao[1] > atual->posicao[1]){
	        temp[0] = atual->posicao[0];
	        temp[1] = atual->posicao[1];
	        atual->posicao[0] = anterior->posicao[0];
	        atual->posicao[1] = anterior->posicao[1];
	        anterior->posicao[0] = temp[0];
	        anterior->posicao[1] = temp[1];
	    }
	    atual = atual->prox;
	}
        anterior = anterior->prox;
    }
}
