#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 256

int main(int argc, char**argv)
{
  // === pid_t === do reprezentowania ID procesow =====
  pid_t pid;
  int potok[2], fd, n;
  char buf[BUF_SIZE];
  // === Stworz potok ==================================
  if(pipe(potok) < 0)
    {
      fprintf(stderr, "Failed creating pipe\n");
      return 1;
    }
  // === Stworz dziecko === (dziecko=0;rodzic>0) =======
  pid = fork();
  // === Jesli dziecko =================================
  if(pid == 0)
    {
      close(potok[1]);
      close(0);
      // === przypisz wyjscie potoku do STDIN ==========
      dup(potok[0]);
      close(potok[0]);
      // === display z STDINprocesu na STDOUTprocesu ===
      execlp("display", "display", NULL);
    }
  // === Jesli rodzic ==================================
  else
    {
      close(potok[0]);
      if((fd = open(argv[1], O_RDONLY)) < 0)
	{
	  fprintf(stderr, "Blad! Nie otworzono pliku.\n");
	  return 2;
        }
      while((n = read(fd, &buf, BUF_SIZE)) > 0)
	{
	  if(write(potok[1], &buf, n) < 0)
	    {
	      fprintf(stderr, "Blad! Nie zapisano do potoku.\n");
	      return 3;
            }  
	}
      // === Dziecko wyswietli obraz dopiero po zamknieciu potoku ===
      //sleep(2);
      //close(potok[1]);
      close(fd);
    }
}
