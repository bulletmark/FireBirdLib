#include "../libFireBird.h"

inline dword FIS_vciplusMenuMode(void)
{
  static dword          vciplusMenuMode = 0;

  if (!vciplusMenuMode)
    vciplusMenuMode = TryResolve("_ciplusMenuMode");

  return vciplusMenuMode;
}
