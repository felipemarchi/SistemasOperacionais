//Estrutura para lista encadeada de resultados
typedef struct Lista_Resultados{
    int posicao[2];
    struct Lista_Resultados *prox;
}lista;

//Estrutura de argumentos para threads
typedef struct Argumentos{
    int idThread;
    float valorBusca;
    int nLinhas;
    int nColunas;
    int nThreads;
    int nLeituras;
    int posicaoInicial;
    char nomeArquivo[30];
}argumentos;

//Protótipos das funções principais
int buscaValores(float, int, int, int, char nomeArquivo[30]);
void *threadBuscaValores(void *);
void imprimeResultados(lista *);

//Protótipos das funções de manipulação de lista
int inicializarLista(lista **);
void insereListaFim(lista **, int, int);
void ordenarLista(lista **);
