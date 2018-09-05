#include "libFireBird.h"

inline dword FIS_fwSetIrCode(void)
{
  TRACEENTER;

  static dword          fwSetIrCode = 0;

  if(!fwSetIrCode)
    fwSetIrCode = TryResolve("DevFront_SetIrCode");

  TRACEEXIT;
  return fwSetIrCode;
}
