#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimeInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockTimeInfo");
  #endif

  static dword          *vFlashTimeInfo = 0;

  if(!vFlashTimeInfo)
    vFlashTimeInfo = (dword*)TryResolve("_timeInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashTimeInfo ? *vFlashTimeInfo : 0);
}
