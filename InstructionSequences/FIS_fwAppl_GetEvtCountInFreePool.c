#include "libFireBird.h"

inline dword FIS_fwAppl_GetEvtCountInFreePool(void)
{
  TRACEENTER;

  static dword          _Appl_GetEvtCountInFreePool = 0;

  if(!_Appl_GetEvtCountInFreePool)
    _Appl_GetEvtCountInFreePool = TryResolve("_Z26Appl_GetEvtCountInFreePoolv");

  TRACEEXIT;
  return _Appl_GetEvtCountInFreePool;
}
