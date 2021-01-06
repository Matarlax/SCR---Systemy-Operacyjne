#include <pthread.h>
#include <stdio.h>

void *HelloSCR(void *threadID)
{
  long ID=(long)threadID;
  printf("Hello SCR. Written by thread %ld\n", ID);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[5];
  for(long ID=0;ID<5;ID++)
    if ( pthread_create(&threads[ID], NULL, HelloSCR, (void *)ID) )
      {
	fprintf(stderr,"Blad! Nie stworzono watku.");
	return 1;
      }
  pthread_exit(NULL);
}
