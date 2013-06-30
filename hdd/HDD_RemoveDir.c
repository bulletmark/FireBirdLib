#include                <stdio.h>
#include                <stdlib.h>
#include                "../libFireBird.h"

void HDD_RemoveDir(char *DirPath, bool Recursive)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_RemoveDir");
  #endif

  char                  cmd[512];

  if(DirPath && *DirPath)
  {
    if(Recursive)
      TAP_SPrint(cmd, "rm -rf %s/%s", TAPFSROOT, DirPath);
    else
      TAP_SPrint(cmd, "rmdir %s/%s", TAPFSROOT, DirPath);

    system(cmd);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
