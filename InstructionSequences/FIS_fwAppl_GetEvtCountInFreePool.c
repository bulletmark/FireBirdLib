#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtCountInFreePool(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetEvtCountInFreePool");
  #endif

  static dword          _Appl_GetEvtCountInFreePool = 0;

  if(!_Appl_GetEvtCountInFreePool)
    _Appl_GetEvtCountInFreePool = TryResolve("_Z26Appl_GetEvtCountInFreePoolv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetEvtCountInFreePool;
}
