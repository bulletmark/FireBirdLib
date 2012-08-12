#include "../libFireBird.h"

inline dword FIS_vFlashBlockTransponderInfo(void)
{
  static dword          *vFlashTPInfo = 0;

  if(!vFlashTPInfo)
  {
    vFlashTPInfo = (dword*)TryResolve("_tpInfo");
    if(!vFlashTPInfo) return 0;
  }

  return *vFlashTPInfo;
}
