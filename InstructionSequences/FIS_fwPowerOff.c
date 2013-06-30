#include "../libFireBird.h"

inline dword FIS_fwPowerOff(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwPowerOff");
  #endif

  static dword          fwPowerOff = 0;

  if(!fwPowerOff)
    fwPowerOff = TryResolve("_Z21Appl_EvtProc_PowerOffjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwPowerOff;
}
