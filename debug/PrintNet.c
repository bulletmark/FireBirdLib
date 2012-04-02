#include                <sys/ioctl.h>
#include                <linux/hdreg.h>
#include                <linux/fs.h>
#include                <fcntl.h>
#include                <unistd.h>
#include                <string.h>

#ifdef _TMSEMU_
  #include              "tap_tmsemu.h"
#else
  #include              "tap.h"
#endif

void PrintNet(char *puffer)
{
  int                   i = 0;
  int                   fd;
  char                  fn[12];

  do
  {
    TAP_SPrint(fn, "/dev/pts/%d", i);
    fd = open(fn, O_RDWR);
    if(fd)
    {
      write(fd, puffer, strlen(puffer) + 1);
      close(fd);
      return;
    }
    i++;
  }
  while(i < 20);
}
