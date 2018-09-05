#include "libFireBird.h"

inline dword FIS_vFlash(void)
{
  TRACEENTER;

  static dword          vFlash = 0;

  if(!vFlash)
  {
    dword *_applFlashAddr = (dword*)TryResolve("_applFlashAddr");

    if(!_applFlashAddr) return 0;
    vFlash = *_applFlashAddr;
  }

  TRACEEXIT;
  return vFlash;
}
