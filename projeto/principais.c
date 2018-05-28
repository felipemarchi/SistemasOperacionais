#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "principais.h"

//Variáveis globais do programa
lista *inicio;
pthread_t threadID[16];
argumentos vArgumentos[16];

/**
 * Função que cria threads passando os argumentos necessários para busca
 * também pede ao programa esperar as threads terminarem
 *
 * @param valorBusca - valor a ser buscado na matriz
 * @param m - número de linhas da matriz
 * @param n - número de colunas da matriz
 * @param nThreads - número de theads para executar
 * @param nomeArquivo - nome do arquivo da matriz
 *
 * @return 0 - Sucesso
 * @return 1 - Erro ao inicializar lista 
**/
int buscaValores(float valorBusca,int m,int n,int nThreads,char nomeArquivo[30]){
    //Função depende da inicilização da lista
    if(!inicializarLista(&inicio)){

        register int i;
        int nLeituras = m*n/nThreads;

        //Cria threads passando argumentos necessários
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

        //Faz com que a main() não termine antes
        for(i=0; i<nThreads; i++)
            pthread_join(threadID[i], NULL);

    }else{
        printf("\nNao foi possivel inicializar a lista!\n");
	return 1;
    }
    return 0;
}

/**
 * Função que representa uma thread genérica que deve percorrer
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

    //Calcula índice linha segundo posição inicial
    int linha;
    if(argumentos->posicaoInicial%argumentos->nColunas > 0 || argumentos->posicaoInicial/argumentos->nColunas == 0)
        linha = argumentos->posicaoInicial/argumentos->nColunas;
    else
        linha = argumentos->posicaoInicial/argumentos->nColunas - 1;

    //Calcula índice coluna segundo posição inicial
    int coluna;
    if(argumentos->posicaoInicial-argumentos->nColunas < 0)
        coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas + argumentos->nColunas;
    else if((argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas == 0)
        coluna = argumentos->nColunas;
    else
	coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas;
    coluna--;

    //Percorre matriz até a posição inicial
    float procura;
    register int i;
    argumentos->posicaoInicial--;
    for(i=1;i<=argumentos->posicaoInicial;i++){
        fscanf(arquivo,"%f",&procura);
    }

    //Lê e compara nLeitura vezes
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
    //Ou até o final do arquivo, se for o caso
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
 * Função que imprime posições ordenadas da matriz
 * onde o valor buscado se encontra
 *
 * @param *inicio - lista encadeada a ser impressa
**/
void imprimeResultados(lista *inicio){
    lista *percorre;

    //Não existe valores na lista
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

//FUNÇÕES DE MANIPULAÇÃO DA LISTA

/**
 * Função que inicializa lista encadeada
 *
 * @param **inicio = endereço de memória da lista a ser inicializada
 *
 * @return 0 - Sucesso
**/
int inicializarLista(lista **inicio){
    *inicio = NULL;
    return 0;
}

/**
 * Função que insere a posição encontrada no fim da lista encadeada
 *
 * @param **inicio = endereço de memória da lista a ser inserida
 * @param linha = índice da linha da matriz na posição do elemento encontrado
 * @param coluna = índice da coluna da matriz na posição do elemento encontrado
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
 * Função que ordena posições da lista
 *
 * @param **inicio - endereço de memória da lista a ser ordenada
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
    //porém agrupando por linhas já ordenadas
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
