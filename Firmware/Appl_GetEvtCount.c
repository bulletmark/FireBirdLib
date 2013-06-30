#include                "../libFireBird.h"

dword Appl_GetEvtCount(byte SatIdx, word NetID, word TSID, word ServiceID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetEvtCount");
  #endif

  dword (*__Appl_GetEvtCount)(byte SatIdx, word NetID, word TSID, word ServiceID);
  dword ret = 0;

  __Appl_GetEvtCount = (void*)FIS_fwAppl_GetEvtCount();
  if(__Appl_GetEvtCount) ret = __Appl_GetEvtCount(SatIdx, NetID, TSID, ServiceID);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
