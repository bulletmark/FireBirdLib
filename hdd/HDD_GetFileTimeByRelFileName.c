#include                <stdio.h>
#include                "../libFireBird.h"

dword HDD_GetFileTimeByRelFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetFileTimeByRelFileName");
  #endif

  char                  AbsFileName[256];
  dword                 ret;

  if(FileName)
  {
    TAP_SPrint(AbsFileName, "%s%s", TAPFSROOT, FileName);
    ret = HDD_GetFileTimeByAbsFileName(AbsFileName);
  }
  else ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
