#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 2

int main(int argc, char ** argv)
{
  // === pid_t === do reprezentowania ID procesow =====
  pid_t pid;
  int potok[2], des_plik, n;
  char buf[BUF_SIZE];
  // === Stworz potok ==================================
  if(pipe(potok) < 0)
    {
      fprintf(stderr, "Blad! Nie stworzono potoku.\n");
      return 1;
    }
  // === Stworz dziecko === (dziecko=0;rodzic>0) =======
  pid = fork();
  // === Jesli dziecko =================================
  if(pid == 0)
    {
      close(potok[1]);
      while(read(potok[0], &buf, BUF_SIZE) > 0)
	{
	  write(STDOUT_FILENO, "#", 1);
	  write(STDOUT_FILENO, &buf, BUF_SIZE);
	  write(STDOUT_FILENO, "#", 1);	
	}
      close(potok[0]); 
    }
  // === Jesli rodzic ==================================
  else
    {
      close(potok[0]);
      if((des_plik = open(argv[1], O_RDONLY)) < 0)
	{
	  fprintf(stderr, "Blad! Nie otworzono pliku.\n");
	  return 2;
        }
      while((n = read(des_plik, &buf, BUF_SIZE)) > 0)
	{
	  if(write(potok[1], &buf, n) < 0)
	    {
	      fprintf(stderr, "Blad! Nie zapisano do potoku.\n");
	      return 3;
            }  
	}
      close(des_plik);
    }
}
