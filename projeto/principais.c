#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.h"

struct Argumentos{
    int inicio;
    int nLeituras;
    float procura;
    int linha;
    int coluna;
    char arquivo[30];
    float valorBusca;
};

struct Lista_Resultados{
    int posicao[2];
    struct Lista *prox;
}lista;

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

void buscaValores(int nThreads,float valorBusca,int nLeituras,char arquivo[30]){
    register int i;

    for(i=0; i<nThreads; i++){
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

    printf("\nThread funcionando...");
    printf("\nEsta deve ler %d valores da matriz do arquivo ""%s.txt"" em busca do elemento %f partindo do elemento %d\n", threadArgumentos->nLeituras,threadArgumentos->arquivo,threadArgumentos->valorBusca,threadArgumentos->inicio);


    // Achando linha
    if(threadArgumentos->inicio % nColunas)
        threadArgumentos->linha = threadArgumentos->inicio/nColunas;
    else
        threadArgumentos->linha = (elemento/nColunas)-1;

    // Achando coluna
    if(threadArgumentos->inicio%nLinhas == 0)
        threadArgumentos->coluna = nLinhas - 1;
    else
        threadArgumentos->coluna = (elemento%nLinhas)-1;

    for(i=1;i<threadArgumentos->inicio;i++){
        fscanf("%f",&procura);
    }

    for(i=0;i<threadArgumentos->nLeituras;i++){
        fscanf("%f",&procura);
        if(procura == threadArgumentos->valorBusca){//Se encontrar o valorBusca
            Inserir_fim_LS (&inicio, threadArgumentos->linha, threadArgumentos->coluna)
        }

        if(threadArgumentos->coluna == nColunas){//Ir para a próxima posição
            threadArgumentos->coluna = 0;
            threadArgumentos->linha++;
        }
    }

    //brenda, utilize as variaveis desses prints como exemplo
    //pode apaga-los assim que entender, bem como estes comentarios
    //seu objetivo a partir daqui eh abrir o arquivo e percorrer a matriz
    //em busca do valorBusca
    //se encontrar, utilize a variavel global lista para guardar sua posicao

    pthread_exit(NULL);
}



