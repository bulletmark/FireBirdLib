#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInHash(void)
{
  static dword          _Appl_GetEvtListHeadInHash = 0;

  if (!_Appl_GetEvtListHeadInHash)
    _Appl_GetEvtListHeadInHash = TryResolve("_Z25Appl_GetEvtListHeadInHashttt");

  return _Appl_GetEvtListHeadInHash;
}
