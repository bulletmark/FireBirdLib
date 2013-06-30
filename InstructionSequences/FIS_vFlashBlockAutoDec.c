#include "../libFireBird.h"

inline dword FIS_vFlashBlockAutoDec(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockAutoDec");
  #endif

  static dword          *vFlashAutoDec = 0;

  if(!vFlashAutoDec)
    vFlashAutoDec = (dword*)TryResolve("_autoDec");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashAutoDec ? *vFlashAutoDec : 0);
}
