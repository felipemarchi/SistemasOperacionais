# Projeto 1 -- "Localiza na Matriz"
## Objetivo
Este projeto visa a criação de um programa que utilize múltiplas *threads* para procurar um determinado valor em uma matriz M x N (com M linhas e N colunas) e a análise do desempenho desse programa com 2, 4, 8 e 16 *threads*. 

O programa deverá ser escrito para o sistema operacional Linux e obrigatoriamente utilizar a biblioteca POSIX Threads.

## Descrição do problema a ser resolvido
Considere uma matriz M x N (M linhas, N colunas) que contém valores em ponto flutuante, positivos ou negativos. O programa deverá utilizar múltiplos *threads* para encontrar um determinado valor nessa matriz.

O programa deverá considerar os seguintes fatos:
* A matriz contém números reais, aleatórios, não ordenados.
* A matriz pode ter valores repetidos. Nesse caso, todas as posições em que o elemento ocorrer devem ser apontadas na saída do programa.
* Pode ser que o elemento não conste da matriz.

## Entradas e saídas de valores para o programa
**Entradas**: os valores M, N, T, V -- respectivamente, número de linhas; número de colunas; número de threads; e o valor a ser buscado -- devem ser informados pelo usuário no início do programa, bem como o arquivo onde estão os dados (valores) da matriz. Para os testes, considere valores grandes (maiores ou iguais a 100) para M e N.

**Saídas**: as posições (linha e coluna) onde está cada elemento encontrado, ordenadas de acordo com a posição na matriz; ou uma mensagem informando que o elemento não foi encontrado.