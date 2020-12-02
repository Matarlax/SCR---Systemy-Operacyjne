/*
// Program zatrzyma sie na otwieraniu potokuFIFO
az do wywolania w drugim terminalu polecenia:
$tail -c +1 -f FifoPipe
Dzieje sie tak, poniewaz open blokuje potok
az do obecnosci procesu piszacego i czytajacego.
Mozna to obejsc wywolujac open z O_NONBLOCK.
// close(pipe) rozlacza powiazanie fifo z procesem.
// unlink(pipe) usuwa plik potoku FIFO.
*/

#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <errno.h> // do bledow mkfifo();
#include <sys/stat.h> // do mkfifo
#define BUF_SIZE 2

int main(int argc, char ** argv)
{
  int fd_plik, fd_fifo, n;
  char buf[BUF_SIZE];
  char* fifo_name="FifoPipe";
  // === Stworz FIFO ============================================
  if( mkfifo(fifo_name,0777) < 0)
    {
      if(errno==EEXIST)
	fprintf(stderr,"FIFO juz istnieje!\n");
      else
	{
	  fprintf(stderr,"Blad tworzenia FIFO!\n");
	  return 1;
	}
    }
  for(int i=1;i<argc;++i)
    {
      // === Otwieranie FIFO ====================================
      if( (fd_fifo=open(fifo_name, O_WRONLY)) < 0 )
	{
	  fprintf(stderr, "Blad! Nie otworzono FIFO.\n");
	  return 2;
	}
      // === Otwieranie pliku ===================================
      if((fd_plik = open(argv[i], O_RDONLY)) < 0)
	{
	  fprintf(stderr, "Blad! Nie otworzono pliku.\n");
	  return 3;
	}
      // === Czytanie pliku i wpisywanie do FIFO ================
      while((n = read(fd_plik, &buf, BUF_SIZE)) > 0)
	{
	  if(write(fd_fifo, &buf, n) < 0)
	    {
	      fprintf(stderr, "Blad! Nie zapisano do potoku.\n");
	      return 4;
	    }  
	}
      write(fd_fifo,"\n",1); // odstep miedzy plikami
      close(fd_plik);
      close(fd_fifo);
      sleep(5);
    }
  return 0;
}
