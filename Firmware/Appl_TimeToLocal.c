#include                "../libFireBird.h"

dword Appl_TimeToLocal(dword UTCTime)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_TimeToLocal");
  #endif

  dword (*__Appl_TimeToLocal)(dword);
  dword ret = 0;

  __Appl_TimeToLocal = (void*)FIS_fwAppl_TimeToLocal();
  if(__Appl_TimeToLocal) ret = __Appl_TimeToLocal(UTCTime);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
