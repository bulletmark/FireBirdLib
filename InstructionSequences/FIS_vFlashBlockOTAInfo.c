#include "../libFireBird.h"

inline dword FIS_vFlashBlockOTAInfo(void)
{
  static dword          *vFlashOtaInfo = 0;

  if(!vFlashOtaInfo)
  {
    vFlashOtaInfo = (dword*)TryResolve("_otaInfo");
    if(!vFlashOtaInfo) return 0;
  }

  return *vFlashOtaInfo;
}
