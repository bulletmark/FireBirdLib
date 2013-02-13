#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInUsePool(void)
{
  static dword          _Appl_GetEvtListHeadInUsePool = 0;

  if (!_Appl_GetEvtListHeadInUsePool)
    _Appl_GetEvtListHeadInUsePool = TryResolve("_Z28Appl_GetEvtListHeadInUsePoolv");

  return _Appl_GetEvtListHeadInUsePool;
}
