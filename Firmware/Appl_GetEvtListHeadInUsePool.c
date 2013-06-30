#include                "../libFireBird.h"

dword *Appl_GetEvtListHeadInUsePool(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetEvtListHeadInUsePool");
  #endif

  dword *(*__Appl_GetEvtListHeadInUsePool)(void);
  dword *ret = NULL;

  __Appl_GetEvtListHeadInUsePool = (void*)FIS_fwAppl_GetEvtListHeadInUsePool();
  if(__Appl_GetEvtListHeadInUsePool) ret = __Appl_GetEvtListHeadInUsePool();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
