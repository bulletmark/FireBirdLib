#include                "libFireBird.h"

dword *Appl_GetEvtListHeadInUsePool(void)
{
  TRACEENTER;

  dword *(*__Appl_GetEvtListHeadInUsePool)(void);
  dword *ret = NULL;

  __Appl_GetEvtListHeadInUsePool = (void*)FIS_fwAppl_GetEvtListHeadInUsePool();
  if(__Appl_GetEvtListHeadInUsePool) ret = __Appl_GetEvtListHeadInUsePool();

  TRACEEXIT;
  return ret;
}
