#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtListHeadInUsePool(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetEvtListHeadInUsePool");
  #endif

  static dword          _Appl_GetEvtListHeadInUsePool = 0;

  if(!_Appl_GetEvtListHeadInUsePool)
    _Appl_GetEvtListHeadInUsePool = TryResolve("_Z28Appl_GetEvtListHeadInUsePoolv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetEvtListHeadInUsePool;
}
