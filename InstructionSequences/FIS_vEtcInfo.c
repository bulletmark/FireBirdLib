#include "../libFireBird.h"

inline dword FIS_vEtcInfo(void)
{
  static dword          vEtcInfo;

  if(!vEtcInfo)
  {
    vEtcInfo = TryResolve("_etcInfo");
    if(vEtcInfo) vEtcInfo = *(dword*)vEtcInfo;
  }

  return vEtcInfo;
}
