#include "../libFireBird.h"

inline dword FIS_vFlashBlockLanIPConfig(void)
{
  TRACEENTER();

  static dword          *vFlashOldLanIpConfig = 0;

  if(!vFlashOldLanIpConfig)
    vFlashOldLanIpConfig = (dword*)TryResolve("_oldLanIpConfig");

  TRACEEXIT();
  return (vFlashOldLanIpConfig ? *vFlashOldLanIpConfig : 0);
}
