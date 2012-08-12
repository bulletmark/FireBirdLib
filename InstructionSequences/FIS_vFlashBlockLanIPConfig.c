#include "../libFireBird.h"

inline dword FIS_vFlashBlockLanIPConfig(void)
{
  static dword          *vFlashOldLanIpConfig = 0;

  if(!vFlashOldLanIpConfig)
  {
    vFlashOldLanIpConfig = (dword*)TryResolve("_oldLanIpConfig");
    if(!vFlashOldLanIpConfig) return 0;
  }

  return *vFlashOldLanIpConfig;
}
