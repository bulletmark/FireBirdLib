#include "libFireBird.h"

inline dword FIS_vBootReason(void)
{
  TRACEENTER;

  static dword          vBootReason = 0;

  if(!vBootReason)
    vBootReason = TryResolve("_powerOnSrc");

  TRACEEXIT;
  return vBootReason;
}
