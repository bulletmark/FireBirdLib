#include "../libFireBird.h"

inline dword FIS_fwAppl_SetTimeShift(void)
{
  static dword          fwAppl_SetTimeShift = 0;

  if (!fwAppl_SetTimeShift)
    fwAppl_SetTimeShift = TryResolve("_Z17Appl_SetTimeShifti");

  return fwAppl_SetTimeShift;
}
