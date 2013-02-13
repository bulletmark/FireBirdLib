#include                "../libFireBird.h"

dword Appl_GetEvtCountInFreePool(void)
{
  dword (*__Appl_GetEvtCountInFreePool)(void);
  dword ret = 0;

  __Appl_GetEvtCountInFreePool = (void*)FIS_fwAppl_GetEvtCountInFreePool();
  if(__Appl_GetEvtCountInFreePool) ret = __Appl_GetEvtCountInFreePool();

  return ret;
}
