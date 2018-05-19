#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <unistd.h>  // Cabe�alho para a fun��o sleep
#include <pthread.h> // Cabe�alho espec�fico para threads POSIX
#include "funcoes.c" // Cabe�alho para a fun��es que ser�o os threads.*/

int valid_follower(char c){ //Fun��o para tratar caracteres
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
        do{//Valida��o de todos os caracteres
            if(!valid_follower(validator))
                valid = 0;
            i++;
            validator = linhas[i];
        }while(validator!='\n');

        if(!valid){//Caso seja inv�lido uma mensagem aparecer� na tela
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        }
        else
            linhas[i] = ' ';// transforma��o do '\n' para ' '
    }while(!valid);//Caso seja inv�lido o processo deve-se repetir

    do{
        i = 0;
        valid = 1;
        printf("\nN: ");//Entrada das colunas
        fgets(colunas,6,stdin);

        validator = colunas[i];
        do{//Valida��o de todos os caracteres
            if(!valid_follower(validator))
                valid = 0;
            i++;
            validator = colunas[i];
        }while(validator!='\n');

        if(!valid){//Caso seja inv�lido uma mensagem aparecer� na tela
            printf("Caractere invalido!\n");
            printf("Digite novamente...\n");
        }
        else
            colunas[i] = ' ';// transforma��o do '\n' para ' '
    }while(!valid);//Caso seja inv�lido o processo deve-se repetir

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
pthread_t meutid;        // Vari�vel que armazena o id do thread principal
pthread_t outrosTIDs[2]; // Vetor que armazena o id dos outros threads

meutid = pthread_self(); // Fun��o que captura o id do thread.
 printf ("Meu Thread ID  = %ld\n",meutid);

 printf("Disparando Thread Func1");
*
 * A fun��o a seguir cria um thread (linha de execu��o) para a fun��o "func1".
 * O prot�tipo da fun��o �:
 *   int pthread_create(pthread_t *thread,  const  pthread_attr_t *attr,
 *                      void *(*start_routine, void*), void *arg);
 * Onde:
 *   "thread" � o identificador do thread que se quer criar.
 *   "attr" s�o os atributos do Thread (Geralmente NULL).
 *   "start_routine" � a fun��o onde est�o os threads.
 *   "arg" s�o os par�metros da "start_routine".
 * A fun��o retorna

 pthread_create(&outrosTIDs[0], NULL, sub_a, NULL);
 printf("(id = %ld)\n", outrosTIDs[0]);


 printf("Disparando Thread Func2");
*
 * A fun��o a seguir cria um thread (linha de execu��o) para a fun��o "func2".

 pthread_create(&outrosTIDs[1], NULL, sub_b, NULL);
 printf("(id = %ld)\n", outrosTIDs[1]);

 printf("Aguardando finalizacao dos Threads id=%ld e id=%ld\n",
        outrosTIDs[0], outrosTIDs[1]);

*
 * A fun��o a seguir bloqueia o processo at� que o thread indicado termine.
 * O prot�tipo da fun��o �:
 *   int pthread_join(pthread_t thread, void **value_ptr);
 * Onde:
 *   "thread" � o identificador do thread que se espera terminar.
 *   "value_ptr" � o valor de retorno da fun��o
 * A fun��o retorna 0 se funcionou corretamente e um valor
 * diferente de 0 para indicar erro.

 pthread_join(outrosTIDs[1], NULL);
 pthread_join(outrosTIDs[0], NULL);
 printf("Threads id=%ld e id=%ld finalizados\n", outrosTIDs[0], outrosTIDs[1]);
*/
