#include "FBLib_hdd.h"
#include "libFireBird.h"

int SendHDDCommand(dword Command, const byte *CommandBlock, int BufferSize)
{
  TRACEENTER();

  #include                <sys/ioctl.h>
  #include                <unistd.h>
  #include                <linux/hdreg.h>
  #include                <fcntl.h>
  #include                <linux/fs.h>

  int                   fd, ret, i;
  unsigned short int    *p;

  //Open the hard drive
  fd = open("/dev/sda", O_RDONLY | O_NONBLOCK);
  //fd = open("/dev/sdb", O_RDONLY | O_NONBLOCK);
  if(fd < 0)
  {
    TRACEEXIT();
    return 1;
  }

  //DumpMemory(CommandBlock, 7, 16);

  ret = ioctl(fd, Command, CommandBlock);

  //DumpMemory(CommandBlock, 7, 16);

  close(fd);

  if(ret)
  {
    TRACEEXIT();
    return 1;
  }

  //Swap endianess of the whole buffer
  p = (unsigned short int*)&CommandBlock[4];
  i = BufferSize;
  while(i > 0)
  {
    endian_swap_word(p);
    p++;
    i -= 2;
  }

  TRACEEXIT();
  return 0;
}
