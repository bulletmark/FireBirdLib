#include                "../libFireBird.h"

void *Appl_GetCurrentEvent(byte SatIndex, word NetID, word TSID, word ServiceID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetCurrentEvent");
  #endif

  void *(*__Appl_GetCurrentEvent)(byte SatIndex, word NetID, word TSID, word ServiceID);
  void *ret = NULL;

  __Appl_GetCurrentEvent = (void*)FIS_fwAppl_GetCurrentEvent();
  if(__Appl_GetCurrentEvent) ret = __Appl_GetCurrentEvent(SatIndex, NetID, TSID, ServiceID);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
