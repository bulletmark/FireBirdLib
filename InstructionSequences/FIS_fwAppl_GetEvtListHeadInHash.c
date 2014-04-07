#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInHash(void)
{
  TRACEENTER();

  static dword          _Appl_GetEvtListHeadInHash = 0;

  if(!_Appl_GetEvtListHeadInHash)
    _Appl_GetEvtListHeadInHash = TryResolve("_Z25Appl_GetEvtListHeadInHashttt");

  TRACEEXIT();
  return _Appl_GetEvtListHeadInHash;
}
