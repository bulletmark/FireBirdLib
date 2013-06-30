#include "../libFireBird.h"

inline dword FIS_vFlashBlockOTAInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockOTAInfo");
  #endif

  static dword          *vFlashOtaInfo = 0;

  if(!vFlashOtaInfo)
    vFlashOtaInfo = (dword*)TryResolve("_otaInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashOtaInfo ? *vFlashOtaInfo : 0);
}
