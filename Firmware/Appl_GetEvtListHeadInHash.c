#include                "../libFireBird.h"

dword *Appl_GetEvtListHeadInHash(word NetID, word TSID, word ServiceID)
{
  dword *(*__Appl_GetEvtListHeadInHash)(word NetID, word TSID, word ServiceID);
  dword *ret = NULL;

  __Appl_GetEvtListHeadInHash = (void*)FIS_fwAppl_GetEvtListHeadInHash();
  if(__Appl_GetEvtListHeadInHash) ret = __Appl_GetEvtListHeadInHash(NetID, TSID, ServiceID);

  return ret;
}
