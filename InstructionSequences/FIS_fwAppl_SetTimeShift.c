#include "libFireBird.h"

inline dword FIS_fwAppl_SetTimeShift(void)
{
  TRACEENTER;

  static dword          fwAppl_SetTimeShift = 0;

  if(!fwAppl_SetTimeShift)
    fwAppl_SetTimeShift = TryResolve("_Z17Appl_SetTimeShifti");

  TRACEEXIT;
  return fwAppl_SetTimeShift;
}
