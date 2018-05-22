#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.h"

struct Argumentos{
    int inicio;
    int nLeituras;
    char arquivo[30];
    float valorBusca;
};

struct Lista_Resultados{
    int posicao[2];
    struct Lista *prox;
}lista;

pthread_t threadID[16];
struct Argumentos vArgumentos[16];

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

    //brenda, utilize as variaveis desses prints como exemplo
    //pode apaga-los assim que entender, bem como estes comentarios
    //seu objetivo a partir daqui eh abrir o arquivo e percorrer a matriz
    //em busca do valorBusca
    //se encontrar, utilize a variavel global lista para guardar sua posicao

    pthread_exit(NULL);
}



