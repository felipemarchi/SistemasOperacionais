#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validaCaracteres(char c);

int main(){

    char linhas[6];
    char colunas[6];
    char arquivo[30];
    float valor;
    int threads;

    char comando[100] = "";
    char validador;
    int valido;
    int i;

    printf("ESTE PROGRAMA DEVE BUSCAR UM\n");
    printf("VALOR NUMA MATRIZ ALEATORIA\n");
    printf("UTILIZANDO MULTIPLAS THREADS\n");
    printf("============================\n");

    printf("\n1. Para gerar a matriz, entre com...\n");

    do{
        i = 0;
        valido = 1;

        printf("\nNumero de linhas (M): ");
        fgets(linhas,6,stdin);

        validador = linhas[i];
        do{
            if(!validaCaracteres(validador))
                valido = 0;
            i++;
            validador = linhas[i];
        }while(validador!='\n');

        if(!valido){
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        }else
            linhas[i] = ' ';
    }while(!valido);

    do{
        i = 0;
        valido = 1;

        printf("\nNumero de colunas (N): ");
        fgets(colunas,6,stdin);

        validador = colunas[i];
        do{
            if(!validaCaracteres(validador))
                valido = 0;
            i++;
            validador = colunas[i];
        }while(validador!='\n');

        if(!valido){
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        } else
            colunas[i] = ' ';
    }while(!valido);

    printf("\nNome do arquivo: ");
    scanf("%s",&arquivo);

    printf("\n------------------------------------------------------------\n");
    strcat(comando,"../plugins/generateRandomMatrixDouble ");
    strcat(comando,linhas);
    strcat(comando,colunas);
    strcat(comando,"../arquivos/");
    strcat(comando,arquivo);
    strcat(comando,".txt");
    system(comando);
    printf("------------------------------------------------------------\n");

    getchar();
    printf("\n2. Para buscar um valor na matriz, entre com...\n");    

    printf("\nNumero de threads (T): ");
    scanf("%d",&threads);

    printf("\nValor a ser buscado (V): ");
    scanf("%f",&valor);

    printf("\n------------------------------------------------------------\n");
    printf("Buscando valores na matriz");
    printf("\n------------------------------------------------------------\n");

    return 0;
}

int validaCaracteres(char c){
    if((int)c>=48 && (int)c<=57)
        return 1;
    else
        return 0;
}




