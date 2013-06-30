#include "../libFireBird.h"

inline dword FIS_fwSetIrCode(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwSetIrCode");
  #endif

  static dword          fwSetIrCode = 0;

  if(!fwSetIrCode)
    fwSetIrCode = TryResolve("DevFront_SetIrCode");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwSetIrCode;
}
