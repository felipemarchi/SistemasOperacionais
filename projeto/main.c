#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <unistd.h>  // Cabeçalho para a função sleep
#include <pthread.h> // Cabeçalho específico para threads POSIX
#include "funcoes.c" // Cabeçalho para a funções que serão os threads.*/

int valid_follower(char c){ //Função para tratar caracteres
    if((int)c>=48 && (int)c<=57)
        return 1;
    else
        return 0;
}

int main(){

    //vars
    char linhas[6];
    char colunas[6];
    int threads;
    char valor[20];
    char arquivo[30];

    char comando[100] = "";
    char validator;
    int i;
    int valid;

    //Legendas
    printf("M -> Numero de linhas\n");
    printf("N -> Numero de colunas\n");
    printf("T -> Numero de threads\n");
    printf("V -> Valor a ser buscado na matriz\n");

    printf("\n------------------------------------\n");

    do{
        i = 0;
        valid = 1;
        printf("\nM: ");//Entrada das linhas
        fgets(linhas,6,stdin);

        validator = linhas[i];
        do{//Validação de todos os caracteres
            if(!valid_follower(validator))
                valid = 0;
            i++;
            validator = linhas[i];
        }while(validator!='\n');

        if(!valid){//Caso seja inválido uma mensagem aparecerá na tela
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        }
        else
            linhas[i] = ' ';// transformação do '\n' para ' '
    }while(!valid);//Caso seja inválido o processo deve-se repetir

    do{
        i = 0;
        valid = 1;
        printf("\nN: ");//Entrada das colunas
        fgets(colunas,6,stdin);

        validator = colunas[i];
        do{//Validação de todos os caracteres
            if(!valid_follower(validator))
                valid = 0;
            i++;
            validator = colunas[i];
        }while(validator!='\n');

        if(!valid){//Caso seja inválido uma mensagem aparecerá na tela
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        }
        else
            colunas[i] = ' ';// transformação do '\n' para ' '
    }while(!valid);//Caso seja inválido o processo deve-se repetir

    printf("\nNome do arquivo da matriz: ");//Entrada do nome do arquivo a ser gerado
    scanf("%s",&arquivo);

    strcat(comando,"../plugins/generateRandomMatrixDouble ");
    strcat(comando,linhas);
    strcat(comando,colunas);
    strcat(comando,arquivo);
    strcat(comando,".txt");

    system(comando);

    printf("\nMatriz gerada!\n");

    printf("\nT: ");//Entrada das threads
    scanf("%d",&threads);

    getchar();
    printf("\nV: ");//Entrada do valor a ser buscado na matriz
    scanf("%s",&valor);

return 0;
}

/*
pthread_t meutid;        // Variável que armazena o id do thread principal
pthread_t outrosTIDs[2]; // Vetor que armazena o id dos outros threads

meutid = pthread_self(); // Função que captura o id do thread.
 printf ("Meu Thread ID  = %ld\n",meutid);

 printf("Disparando Thread Func1");
*
 * A função a seguir cria um thread (linha de execução) para a função "func1".
 * O protótipo da função é:
 *   int pthread_create(pthread_t *thread,  const  pthread_attr_t *attr,
 *                      void *(*start_routine, void*), void *arg);
 * Onde:
 *   "thread" é o identificador do thread que se quer criar.
 *   "attr" são os atributos do Thread (Geralmente NULL).
 *   "start_routine" é a função onde estão os threads.
 *   "arg" são os parâmetros da "start_routine".
 * A função retorna

 pthread_create(&outrosTIDs[0], NULL, sub_a, NULL);
 printf("(id = %ld)\n", outrosTIDs[0]);


 printf("Disparando Thread Func2");
*
 * A função a seguir cria um thread (linha de execução) para a função "func2".

 pthread_create(&outrosTIDs[1], NULL, sub_b, NULL);
 printf("(id = %ld)\n", outrosTIDs[1]);

 printf("Aguardando finalizacao dos Threads id=%ld e id=%ld\n",
        outrosTIDs[0], outrosTIDs[1]);

*
 * A função a seguir bloqueia o processo até que o thread indicado termine.
 * O protótipo da função é:
 *   int pthread_join(pthread_t thread, void **value_ptr);
 * Onde:
 *   "thread" é o identificador do thread que se espera terminar.
 *   "value_ptr" é o valor de retorno da função
 * A função retorna 0 se funcionou corretamente e um valor
 * diferente de 0 para indicar erro.

 pthread_join(outrosTIDs[1], NULL);
 pthread_join(outrosTIDs[0], NULL);
 printf("Threads id=%ld e id=%ld finalizados\n", outrosTIDs[0], outrosTIDs[1]);
*/
