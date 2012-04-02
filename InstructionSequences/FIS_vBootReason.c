#include "../libFireBird.h"

inline dword FIS_vBootReason(void)
{
  static dword          vBootReason = 0;

  if(!vBootReason)
    vBootReason = TryResolve("_powerOnSrc");

  return vBootReason;
}
