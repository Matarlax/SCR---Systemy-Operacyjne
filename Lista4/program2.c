#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

/* === Zmienna globalna kontrolujaca ignorowanie SIGUSR1 === */
static int sigusr1_block=10;

void signal_handler(int signal_type)
{
  /* === a) Komunikat i koniec programu ==================== */
  if (signal_type == SIGALRM)
    {
      printf("Przechwycony SIGALRM. Koncze program.\n");
      exit(0);
    }
  /* === b) Komunikat i powrot do programu ================= */
  if (signal_type == SIGTERM)
    printf("Przechwycony SIGTERM. Kontynuuje program.\n");
  /* === c) Wstrzymanie odebrania sygnalu przez 10 petli === */
  if (signal_type == SIGUSR1)
    {
      if(sigusr1_block==10)
	{
	  printf("Przechwycony SIGUSR1. Ignorowany przez 10 petli.\n");
	  sigusr1_block=0;
	}
      /*Jak nie bedzie rowne 10, nie rob nic(ignoruj)*/
    }
}

int main(void)
{
  if (signal(SIGALRM, signal_handler) == SIG_ERR)
    printf("\nNie przechwyci SIGALRM\n");
  if (signal(SIGTERM, signal_handler) == SIG_ERR)
    printf("\nNie przechwyci SIGTERM\n");
  if (signal(SIGUSR1, signal_handler) == SIG_ERR)
    printf("\nNie przechwyci SIGUSR1\n");
  /* === d) Ignoruj SIGUSR2 =================================== */
  if (signal(SIGUSR2, SIG_IGN) == SIG_ERR)
    printf("\nNie zignoruje SIGUSR2\n");
  /* === Petla ++i ============================================ */
  int i=0;
  while(1)
    {
      if(sigusr1_block<10)
	++sigusr1_block;
      ++i;
      printf("Zwiekszam 'i' do %d. Przechodze w sleep(1).\n", i);
      sleep(1);
    }
  return 0;
}
