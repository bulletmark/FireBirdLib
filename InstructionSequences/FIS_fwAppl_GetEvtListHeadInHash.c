#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInHash(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetEvtListHeadInHash");
  #endif

  static dword          _Appl_GetEvtListHeadInHash = 0;

  if(!_Appl_GetEvtListHeadInHash)
    _Appl_GetEvtListHeadInHash = TryResolve("_Z25Appl_GetEvtListHeadInHashttt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetEvtListHeadInHash;
}
