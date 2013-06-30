#include "../libFireBird.h"

inline dword FIS_vFlash(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlash");
  #endif

  static dword          vFlash = 0;

  if(!vFlash)
  {
    dword *_applFlashAddr = (dword*)TryResolve("_applFlashAddr");

    if(!_applFlashAddr) return 0;
    vFlash = *_applFlashAddr;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vFlash;
}
