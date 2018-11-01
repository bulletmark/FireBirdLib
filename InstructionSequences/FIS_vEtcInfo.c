#include "libFireBird.h"

inline dword FIS_vEtcInfo(void)
{
  TRACEENTER();

  static dword          vEtcInfo = 0;

  if(!vEtcInfo)
  {
    vEtcInfo = TryResolve("_etcInfo");
    if(vEtcInfo) vEtcInfo = *(dword*)vEtcInfo;
  }

  TRACEEXIT();
  return vEtcInfo;
}
