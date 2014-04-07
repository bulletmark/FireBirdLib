#include                <string.h>
#include                <stdio.h>
#include                <stdlib.h>
#include                "../libFireBird.h"

void HDD_RemoveDir(char *DirPath, bool Recursive)
{
  TRACEENTER();

  char                  cmd[512], LinuxPath[FBLIB_DIR_SIZE];

  if(DirPath && *DirPath)
  {
    strcpy(cmd, DirPath);
    if(DirPath[strlen(cmd) - 1] != '/') strcat(cmd, "/");
    ConvertPathType(cmd, LinuxPath, PF_LinuxPathOnly);

    if(Recursive)
      TAP_SPrint(cmd, "rm -rf %s", LinuxPath);
    else
      TAP_SPrint(cmd, "rmdir %s", LinuxPath);

    system(cmd);
  }

  TRACEEXIT();
}
