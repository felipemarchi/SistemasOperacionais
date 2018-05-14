/** 
 * Este é um programa simples para exemplificar a utilização de Threads.
 *
 * Desenvolvido por: Prof. M.Sc. André Leon S. Gradvohl
 * E-mail: andre_gradvohl@yahoo.com 
 * 
 * Outros arquivos necessários para a execução desse programa são:
 * - funcoes.h
 * - funcoes.c
 *
 * Última atualização: 14/Fev/2003
 */


/* Inclusão de cabeçalhos*/
#include <stdio.h>
#include <unistd.h>  // Cabeçalho para a função sleep
#include <pthread.h> // Cabeçalho específico para threads POSIX
#include "funcoes.c" // Cabeçalho para a funções que serão os threads.

pthread_t meutid;        /* Variável que armazena o id do thread principal */
pthread_t outrosTIDs[2]; /* Vetor que armazena o id dos outros threads */

int main( void )
{
 meutid = pthread_self(); // Função que captura o id do thread.
 printf ("Meu Thread ID  = %ld\n",meutid);

 printf("Disparando Thread Func1");
/**
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
 */
 pthread_create(&outrosTIDs[0], NULL, sub_a, NULL); 
 printf("(id = %ld)\n", outrosTIDs[0]);


 printf("Disparando Thread Func2");
/**
 * A função a seguir cria um thread (linha de execução) para a função "func2".
 */
 pthread_create(&outrosTIDs[1], NULL, sub_b, NULL);
 printf("(id = %ld)\n", outrosTIDs[1]);

 printf("Aguardando finalizacao dos Threads id=%ld e id=%ld\n", 
        outrosTIDs[0], outrosTIDs[1]);

/**
 * A função a seguir bloqueia o processo até que o thread indicado termine.
 * O protótipo da função é:
 *   int pthread_join(pthread_t thread, void **value_ptr);
 * Onde:
 *   "thread" é o identificador do thread que se espera terminar.
 *   "value_ptr" é o valor de retorno da função
 * A função retorna 0 se funcionou corretamente e um valor 
 * diferente de 0 para indicar erro.
 */
 pthread_join(outrosTIDs[1], NULL);
 pthread_join(outrosTIDs[0], NULL);
 printf("Threads id=%ld e id=%ld finalizados\n", outrosTIDs[0], outrosTIDs[1]);

 return 1;
}
