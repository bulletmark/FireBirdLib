#include "libFireBird.h"

inline dword FIS_vciMenuMode(void)
{
  TRACEENTER;

  static dword          vciMenuMode = 0;

  if(!vciMenuMode)
    vciMenuMode = TryResolve("_ciMenuMode");

  TRACEEXIT;
  return vciMenuMode;
}
