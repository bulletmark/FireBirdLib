#include "../libFireBird.h"

inline dword FIS_fwAppl_IsTimeShifting(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_IsTimeShifting");
  #endif

  static dword          fwAppl_IsTimeShifting = 0;

  if(!fwAppl_IsTimeShifting)
    fwAppl_IsTimeShifting = TryResolve("_Z19Appl_IsTimeShiftingv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_IsTimeShifting;
}
