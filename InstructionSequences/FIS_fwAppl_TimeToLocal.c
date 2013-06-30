#include "../libFireBird.h"

inline dword FIS_fwAppl_TimeToLocal(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_TimeToLocal");
  #endif

  static dword          fwAppl_TimeToLocal = 0;

  if(!fwAppl_TimeToLocal)
    fwAppl_TimeToLocal = TryResolve("_Z16Appl_TimeToLocalj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_TimeToLocal;
}
