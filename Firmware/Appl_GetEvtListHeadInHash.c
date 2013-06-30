#include                "../libFireBird.h"

dword *Appl_GetEvtListHeadInHash(word NetID, word TSID, word ServiceID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetEvtListHeadInHash");
  #endif

  dword *(*__Appl_GetEvtListHeadInHash)(word NetID, word TSID, word ServiceID);
  dword *ret = NULL;

  __Appl_GetEvtListHeadInHash = (void*)FIS_fwAppl_GetEvtListHeadInHash();
  if(__Appl_GetEvtListHeadInHash) ret = __Appl_GetEvtListHeadInHash(NetID, TSID, ServiceID);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
