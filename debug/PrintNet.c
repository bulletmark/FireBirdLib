#include                <fcntl.h>
#include                <unistd.h>
#include                <string.h>
#include                "libFireBird.h"

char PrintNetBuffer[1024];

void PrintNet(char *puffer)
{
  int                   i = 0;
  int                   fd;
  char                  fn[12];

  do
  {
    TAP_SPrint(fn, "/dev/pts/%d", i);
    fd = open(fn, O_RDWR);
    if(fd >= 0)
    {
      write(fd, puffer, strlen(puffer));
      close(fd);

      return;
    }
    i++;
  }
  while(i < 20);
}
