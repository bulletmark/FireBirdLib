#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtCount(void)
{
  static dword          _Appl_GetEvtCount = 0;

  if (!_Appl_GetEvtCount)
    _Appl_GetEvtCount = TryResolve("_Z16Appl_GetEvtCounthttt");

  return _Appl_GetEvtCount;
}
