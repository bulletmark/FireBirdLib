#include                "../libFireBird.h"

dword Appl_GetFreeExtRecordSpace(char *MountPath)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetFreeExtRecordSpace");
  #endif

  dword                 (*__Appl_GetFreeExtRecordSpace)(char *);
  dword                 ret = 0;

  __Appl_GetFreeExtRecordSpace = (void*)FIS_fwAppl_GetFreeExtRecordSpace();
  if(__Appl_GetFreeExtRecordSpace) ret = __Appl_GetFreeExtRecordSpace(MountPath);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
