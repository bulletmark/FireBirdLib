#include "libFireBird.h"

inline dword FIS_fwAppl_IsTimeShifting(void)
{
  TRACEENTER();

  static dword          fwAppl_IsTimeShifting = 0;

  if(!fwAppl_IsTimeShifting)
    fwAppl_IsTimeShifting = TryResolve("_Z19Appl_IsTimeShiftingv");

  TRACEEXIT();
  return fwAppl_IsTimeShifting;
}
