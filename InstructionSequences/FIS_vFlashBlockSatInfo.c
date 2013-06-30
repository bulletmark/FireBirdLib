#include "../libFireBird.h"

inline dword FIS_vFlashBlockSatInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockSatInfo");
  #endif

  static dword          *vFlashSatInfo = 0;

  if(!vFlashSatInfo)
    vFlashSatInfo = (dword*)TryResolve("_satInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashSatInfo ? *vFlashSatInfo : 0);
}
