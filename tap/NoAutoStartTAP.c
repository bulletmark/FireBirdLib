#include                <stdio.h>
#include                <stdlib.h>
#include                <string.h>
#include                "../libFireBird.h"

bool NoAutoStartTAP(void)
{
  TRACEENTER();

  char                  CurrentDir[FBLIB_DIR_SIZE];
  char                  *FileName;
  char                  cmd[200];
  int                   ret;

  ret = 1;

  HDD_TAP_GetCurrentDir(CurrentDir);
  if(strstr(CurrentDir, "/ProgramFiles/AutoStart") || strstr(CurrentDir, "/ProgramFiles/XStart"))
  {
    //The curTapTask variable is not thread safe. Call InitTAPex() if this function will be called from a sub thread
    if(TAP_TableIndex == 0xffffffff)
    {
      dword                *curTapTask;

      curTapTask = (dword*)FIS_vCurTapTask();
      if(!curTapTask)
      {
        TRACEEXIT();
        return -3;
      }
      TAP_TableIndex = *curTapTask;
    }

    HDD_TAP_GetFileNameByIndex(TAP_TableIndex, &FileName);

    TAP_SPrint(cmd, "mv %s /mnt/hd/ProgramFiles", FileName);
    ret = system(cmd);
  }

  TRACEEXIT();
  return (ret == 0);
}
