#include "../libFireBird.h"

inline dword FIS_vFlashBlockTransponderInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockTransponderInfo");
  #endif

  static dword          *vFlashTPInfo = 0;

  if(!vFlashTPInfo)
    vFlashTPInfo = (dword*)TryResolve("_tpInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashTPInfo ? *vFlashTPInfo : 0);
}
