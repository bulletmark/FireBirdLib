#include <stdio.h>
#include "FBLib_hdd.h"

bool HDD_Exist(char *FileName)
{
  TRACEENTER;

  char                  LinuxPath[FBLIB_DIR_SIZE];
  tstat64               statbuf;
  bool                  ret;

  if(!FileName || !*FileName)
  {
    TRACEEXIT;
    return FALSE;
  }

  ConvertPathType(FileName, LinuxPath, PF_FullLinuxPath);
  if(!LinuxPath[0]) ConvertPathType(FileName, LinuxPath, PF_LinuxPathOnly);

  ret = (stat64(LinuxPath, &statbuf) == 0);

  TRACEEXIT;
  return ret;
}
