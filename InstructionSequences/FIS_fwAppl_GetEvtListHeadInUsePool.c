#include "libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInUsePool(void)
{
  TRACEENTER();

  static dword          _Appl_GetEvtListHeadInUsePool = 0;

  if(!_Appl_GetEvtListHeadInUsePool)
    _Appl_GetEvtListHeadInUsePool = TryResolve("_Z28Appl_GetEvtListHeadInUsePoolv");

  TRACEEXIT();
  return _Appl_GetEvtListHeadInUsePool;
}
