#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
 char comando[100] = "";
 char arquivo[25];
 char colunas[5];
 char linhas[5];

 printf("Linhas: ");
 scanf("%s",linhas);
 printf("Colunas: ");
 scanf("%s",colunas);
 printf("File+extension: ");
 scanf("%s",arquivo);

 strcat(comando,"./generateRandomMatrixDouble ");
 strcat(comando,linhas);
 strcat(comando," ");
 strcat(comando,colunas);
 strcat(comando," ");
 strcat(comando,arquivo);

 system(comando);
 return 0;
}
