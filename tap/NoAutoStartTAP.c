#include                <stdio.h>
#include                <stdlib.h>
#include                <string.h>
#include                "../libFireBird.h"

bool NoAutoStartTAP(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("NoAutoStartTAP");
  #endif

  char                  CurrentDir[512];
  char                  *FileName;
  char                  cmd[200];
  dword                *curTapTask;
  int                   ret;

  ret = 1;

  HDD_TAP_GetCurrentDir(CurrentDir);
  if(strstr(CurrentDir, "/ProgramFiles/AutoStart") || strstr(CurrentDir, "/ProgramFiles/XStart"))
  {
    curTapTask = (dword*)FIS_vCurTapTask();
    HDD_TAP_GetFileNameByIndex(*curTapTask, &FileName);

    TAP_SPrint(cmd, "mv %s /mnt/hd/ProgramFiles", FileName);
    ret = system(cmd);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (ret == 0);
}
