/************************************************************************** 
prog01.c - Exemplo sobre como criar um segmento de mem�ria.
Prof. Dr. Jos� Lu�s Zem
Escola de Engenharia de Piracicaba - EEP
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main (int argc, char * argv[]) {

  key_t  key;
  int    shmid, tamanho=2048;

  system("clear");

  key=ftok("/tmp",'a');

  shmid=shmget(key, tamanho, 0600|IPC_CREAT);

  if ( shmid == -1 ) {
     printf("N�o foi poss�vel reservar o segmento de mem�ria.\n");
  } else {
     printf("O identificador e %d.\n",shmid);
  }

  return 0;

}
