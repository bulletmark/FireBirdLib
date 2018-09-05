#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FBLib_tap.h"

bool NoAutoStartTAP(void)
{
  TRACEENTER;

  char                  CurrentDir[FBLIB_DIR_SIZE];
  char                  *FileName;
  char                  cmd[200];
  int                   ret;

  ret = 1;

  HDD_TAP_GetCurrentDir(CurrentDir);
  if(strstr(CurrentDir, "/ProgramFiles/AutoStart") || strstr(CurrentDir, "/ProgramFiles/XStart"))
  {
    if(!LibInitialized && !InitTAPex())
    {
      TRACEEXIT;
      return -3;
    }

    HDD_TAP_GetFileNameByIndex(TAP_TableIndex, &FileName);

    TAP_SPrint(cmd, "mv %s /mnt/hd/ProgramFiles", FileName);
    ret = system(cmd);
  }

  TRACEEXIT;
  return (ret == 0);
}
