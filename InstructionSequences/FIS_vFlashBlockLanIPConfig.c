#include "../libFireBird.h"

inline dword FIS_vFlashBlockLanIPConfig(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockLanIPConfig");
  #endif

  static dword          *vFlashOldLanIpConfig = 0;

  if(!vFlashOldLanIpConfig)
    vFlashOldLanIpConfig = (dword*)TryResolve("_oldLanIpConfig");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashOldLanIpConfig ? *vFlashOldLanIpConfig : 0);
}
