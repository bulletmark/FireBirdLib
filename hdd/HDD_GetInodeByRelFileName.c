#include                <stdio.h>
#include                "../libFireBird.h"

__ino64_t HDD_GetInodeByRelFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetInodeByRelFileName");
  #endif

  char                  AbsFileName[256];
  __ino64_t             ret;

  if(FileName)
  {
    TAP_SPrint(AbsFileName, "%s%s", TAPFSROOT, FileName);
    ret = HDD_GetInodeByAbsFileName(AbsFileName);
  }
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
