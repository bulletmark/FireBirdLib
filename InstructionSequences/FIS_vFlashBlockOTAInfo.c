#include "../libFireBird.h"

inline dword FIS_vFlashBlockOTAInfo(void)
{
  TRACEENTER();

  static dword          *vFlashOtaInfo = 0;

  if(!vFlashOtaInfo)
    vFlashOtaInfo = (dword*)TryResolve("_otaInfo");

  TRACEEXIT();
  return (vFlashOtaInfo ? *vFlashOtaInfo : 0);
}
