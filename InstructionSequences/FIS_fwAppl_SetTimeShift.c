#include "../libFireBird.h"

inline dword FIS_fwAppl_SetTimeShift(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_SetTimeShift");
  #endif

  static dword          fwAppl_SetTimeShift = 0;

  if(!fwAppl_SetTimeShift)
    fwAppl_SetTimeShift = TryResolve("_Z17Appl_SetTimeShifti");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_SetTimeShift;
}
