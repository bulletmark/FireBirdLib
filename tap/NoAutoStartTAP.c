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

  TRACEEXIT();
  return (ret == 0);
}
