#include                "libFireBird.h"

void *Appl_GetCurrentEvent(byte SatIndex, word NetID, word TSID, word ServiceID)
{
  TRACEENTER();

  void *(*__Appl_GetCurrentEvent)(byte SatIndex, word NetID, word TSID, word ServiceID);
  void *ret = NULL;

  __Appl_GetCurrentEvent = (void*)FIS_fwAppl_GetCurrentEvent();
  if(__Appl_GetCurrentEvent) ret = __Appl_GetCurrentEvent(SatIndex, NetID, TSID, ServiceID);

  TRACEEXIT();
  return ret;
}
