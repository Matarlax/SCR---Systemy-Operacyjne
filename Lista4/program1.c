#include <stdio.h>
#include <unistd.h> //sleep(x)

int main()
{
  printf("Przechodze do nieskonczonej petli\n");
  int i=0;
  while(1)
    {
      ++i;
      sleep(1);
    }
  return 0;
}

