#include "../libFireBird.h"

inline dword FIS_vciMenuMode(void)
{
  static dword          vciMenuMode = 0;

  if (!vciMenuMode)
    vciMenuMode = TryResolve("_ciMenuMode");

  return vciMenuMode;
}
