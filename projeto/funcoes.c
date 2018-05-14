#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "funcoes.h" // Cabeçalho que contém o protótipo dessas funções

void *sub_a(void *arg)
{
  register int i=0;
  register int tempoEspera;

  for (i=0;i<30;i+=2)
  {
    tempoEspera =(rand() % 3)+1; //tempo aleatório 1, 2 ou 3 seg.
    printf("\ni = %d. Tempo de Espera: %d\n",i, tempoEspera);
    sleep(tempoEspera); //Dorme um tempo.
  }
  pthread_exit(NULL);
}

void *sub_b(void *arg)
{
  register int j=1;
  register int tempoEspera;

  for (j=1;j<30;j+=2)
  {
    tempoEspera =(rand() % 3)+1; //tempo aleatório 1, 2 ou 3 seg.
    printf("\njota = %d. Tempo de Espera: %d\n",j, tempoEspera);
    sleep(tempoEspera); //Dorme um tempo.
  }
  pthread_exit(NULL);
}
