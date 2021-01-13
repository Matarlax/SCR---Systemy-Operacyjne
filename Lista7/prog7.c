#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define THREADS_NUMBER	20
#define POINTS_AMOUNT   800000
#define SQUARE_SIDE     2

float pi_array[THREADS_NUMBER];

void *BusyWork(void *threadid)
{
  float square_points=0, circle_points=0;
  float x=0, y=0, pi=0;
  for (int i=0; i<POINTS_AMOUNT; i++)
    {
      x=drand48()*SQUARE_SIDE-(float)SQUARE_SIDE/2;
      y=drand48()*SQUARE_SIDE-(float)SQUARE_SIDE/2;
      if(sqrt(x*x+y*y)<=(float)SQUARE_SIDE/2)
	circle_points+=1;
      square_points+=1;
    }
  pi=(float)(4*circle_points/square_points);
  pi_array[(long)threadid]=pi;
  //printf("Cz %f\n",pi);
  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  pthread_t thread[THREADS_NUMBER];
  float pi_sum=0;
  pthread_attr_t attr;
  int rc;
  long t;

  // === Stworz domyslne atrybuty watku ===
  pthread_attr_init(&attr);
  // === Ustaw atrybut watku na mozliwy do dolaczenia ===
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // === Stworz watki ===
  for(t=0; t<THREADS_NUMBER; t++)
    {
    rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
    if (rc) {
      printf("Blad! Tworzenie watku. Kod: %d\n", rc);
      exit(-1);
    }
  }
  
  // === Zniszcz zmienna atrybutow watku ===
  pthread_attr_destroy(&attr);
  // === Poczekaj na watki i ich zsumuj ich wyniki ===
  for(t=0; t<THREADS_NUMBER; t++)
    {
      rc = pthread_join(thread[t], NULL);
      if (rc)
	{
	  printf("Blad! pthread_join(). Kod: %d\n", rc);
	  exit(-1);
	}
      pi_sum+=pi_array[t];
    }

  // === Wyswietl srednie PI ===
  printf("Srednie obliczone PI=%f\n",(pi_sum/THREADS_NUMBER));
  pthread_exit(NULL);
}
