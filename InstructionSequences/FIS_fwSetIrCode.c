#include "../libFireBird.h"

inline dword FIS_fwSetIrCode(void)
{
  static dword          fwSetIrCode = 0;

  if (!fwSetIrCode)
  {
    fwSetIrCode = TryResolve("DevFront_SetIrCode");
  }

  return fwSetIrCode;
}
