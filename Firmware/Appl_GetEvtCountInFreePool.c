#include                "../libFireBird.h"

dword Appl_GetEvtCountInFreePool(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_GetEvtCountInFreePool");
  #endif

  dword (*__Appl_GetEvtCountInFreePool)(void);
  dword ret = 0;

  __Appl_GetEvtCountInFreePool = (void*)FIS_fwAppl_GetEvtCountInFreePool();
  if(__Appl_GetEvtCountInFreePool) ret = __Appl_GetEvtCountInFreePool();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
