/*
//Wzgledem programu podstawowego dodano tylko tworzenie dziecka,
  w ktorym uruchamia sie program 'display'.
//Flaga '-update' powoduje, ze podany plik jest monitorowany
  i jezeli zauwazona zostanie w nim zmiana, display odswiezy sie.
//Petla while-access stworzona aby ominac sytuacje,
  w ktorej display probuje otworzyc nieistniejacy plik.
  sleep(1) uzyty, aby odciazyc procesor
  (Jesli plik nie istnieje, proces glownie spi).
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main()
{
  int fd_txt,fd_map, exist=1;
  char file_name[32];
  char *file_in_memory;
  struct stat file_stat;
  off_t file_size;

  // === Dziecko ================================================
  if(fork()==0)
    {
      // === Szukaj pliku co sekunde ===
      while(exist)
	{
	  exist=access("plik_map",F_OK);
	  sleep(1);
	}
      // === Jesli istnieje to wyskoczy z petli i wyswietli ===
      execlp("display","","-update","1","plik_map",NULL);
    }
  // === Rodzic ================================================
    else
    {
      while(1)
	{
	  // === Otworz plik tekstowy ===
	  do{
	    printf("Podaj nazwe pliku tekstowego:");
	    scanf("%s",file_name);
	  }while((fd_txt=open(file_name,O_RDONLY))<0);
	  // === Ustal dlugosc pliku ===
	  stat(file_name,&file_stat);
	  file_size=file_stat.st_size;
	  // === Stworz plik do mapowania read/write|stworz,uprawnienia ===
	  if((fd_map=open("plik_map",O_RDWR|O_CREAT,S_IRWXU))<0)
	    {
	      printf("Blad! Nie utworzono plik_map.");
	      return 1;
	    }
	  // === Ustaw dlugosc pliku mapowanego ===
	  truncate("plik_map",file_size);
	  // === Mapuj dane pliku do pamieci ===
	  file_in_memory = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd_map,0);
      
	  // === Wyslij dane z pliku do obszaru mapowania  ===
	  read(fd_txt,file_in_memory,file_size);
	  // === Synchronizacja w_pamieci->do_pliku ===
	  msync(file_in_memory,file_size,MS_SYNC);
	  // === Zwolnij mapowany obszar ===
	  munmap(file_in_memory,file_size);
	  // === Zamknij fd ===
	  close(fd_map);
	  close(fd_txt);
	}
    }
  return 0;
}

/*
// stat(sciezka,struktura)
Zwraca parametry pliku o danej lokalizacji do struktury.

// fd_map=open("plik_map",O_RDWR|O_CREAT,S_IRWXU);
dekryptor=otworz(nazwa,read/write|stworz_jak_nie_ma,uprawnienia);
Uprawnienia musza byc jak jest podane O_CREAT,
zeby mozna bylo pozniej sie do niego dostac.

// truncate(lokalizacja,dlugosc);
Ustaw wielkosc pliku na 'dlugosc' w bajtach.
Ucieta pamiec to utracone dane,
a dodana pamiec wypelniana jest null '\0'.

// mmap(*adres,dlugosc,prot,flagi,fd,offset);
Mapowanie pamieci otworzonego pliku 'fd',
o okreslonej 'dlugosci' w bajtach.
Miejsce mapowania wybierane jest przez *adres,
jesli NULL, jadro samo wybiera miejsce.
Ochrona pamieci 'prot' moze ustawic zezwolenie na
czytanie/pisanie/wykonanie/brak_dostepu.
Flaga MAP_SHARED umozliwia dostep do mapowanego pliku
innym procesom mapujacym ten sam obszar.
Offset - gdzie zaczac.

// msync(*adres,dlugosc,flagi);
Synchronizacja pliku mapowanego
z plikiem w pamieci wirtualnej
Flaga MS_SYNC zada aktualizacji i czeka az zakonczy.

// munmap(*adres,dlugosc);
Usuwa mapowany obszar o okreslonej dlugosci.
*adres jest zwracany przez funkcje mmap().
Obszar jest automatycznie odmapowany po zamknieciu procesu,
ale nie po zamknieciu file_deskryptora.
*/
