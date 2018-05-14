/** 
 * Este � um programa simples para exemplificar a utiliza��o de Threads.
 *
 * Desenvolvido por: Prof. M.Sc. Andr� Leon S. Gradvohl
 * E-mail: andre_gradvohl@yahoo.com 
 * 
 * Outros arquivos necess�rios para a execu��o desse programa s�o:
 * - funcoes.h
 * - funcoes.c
 *
 * �ltima atualiza��o: 14/Fev/2003
 */


/* Inclus�o de cabe�alhos*/
#include <stdio.h>
#include <unistd.h>  // Cabe�alho para a fun��o sleep
#include <pthread.h> // Cabe�alho espec�fico para threads POSIX
#include "funcoes.c" // Cabe�alho para a fun��es que ser�o os threads.

pthread_t meutid;        /* Vari�vel que armazena o id do thread principal */
pthread_t outrosTIDs[2]; /* Vetor que armazena o id dos outros threads */

int main( void )
{
 meutid = pthread_self(); // Fun��o que captura o id do thread.
 printf ("Meu Thread ID  = %ld\n",meutid);

 printf("Disparando Thread Func1");
/**
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
 */
 pthread_create(&outrosTIDs[0], NULL, sub_a, NULL); 
 printf("(id = %ld)\n", outrosTIDs[0]);


 printf("Disparando Thread Func2");
/**
 * A fun��o a seguir cria um thread (linha de execu��o) para a fun��o "func2".
 */
 pthread_create(&outrosTIDs[1], NULL, sub_b, NULL);
 printf("(id = %ld)\n", outrosTIDs[1]);

 printf("Aguardando finalizacao dos Threads id=%ld e id=%ld\n", 
        outrosTIDs[0], outrosTIDs[1]);

/**
 * A fun��o a seguir bloqueia o processo at� que o thread indicado termine.
 * O prot�tipo da fun��o �:
 *   int pthread_join(pthread_t thread, void **value_ptr);
 * Onde:
 *   "thread" � o identificador do thread que se espera terminar.
 *   "value_ptr" � o valor de retorno da fun��o
 * A fun��o retorna 0 se funcionou corretamente e um valor 
 * diferente de 0 para indicar erro.
 */
 pthread_join(outrosTIDs[1], NULL);
 pthread_join(outrosTIDs[0], NULL);
 printf("Threads id=%ld e id=%ld finalizados\n", outrosTIDs[0], outrosTIDs[1]);

 return 1;
}
