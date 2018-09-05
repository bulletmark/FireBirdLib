#include "libFireBird.h"

inline dword FIS_vciplusMenuMode(void)
{
  TRACEENTER;

  static dword          vciplusMenuMode = 0;

  if(!vciplusMenuMode)
    vciplusMenuMode = TryResolve("_ciplusMenuMode");

  TRACEEXIT;
  return vciplusMenuMode;
}
