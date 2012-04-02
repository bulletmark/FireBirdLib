#include "../libFireBird.h"

inline dword FIS_fwPowerOff(void)
{
  static dword          fwPowerOff = 0;

  if (!fwPowerOff)
    fwPowerOff = TryResolve("_Z21Appl_EvtProc_PowerOffjj");

  return fwPowerOff;
}
