#include "../libFireBird.h"

inline dword FIS_vEtcInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vEtcInfo");
  #endif

  static dword          vEtcInfo = 0;

  if(!vEtcInfo)
  {
    vEtcInfo = TryResolve("_etcInfo");
    if(vEtcInfo) vEtcInfo = *(dword*)vEtcInfo;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vEtcInfo;
}
