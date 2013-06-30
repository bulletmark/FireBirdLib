#include "../libFireBird.h"

inline dword FIS_vPvrRecTsInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPvrRecTsInfo");
  #endif

  static dword          vpvrRecTsInfo = 0;

  if(!vpvrRecTsInfo)
    vpvrRecTsInfo = TryResolve("_pvrRecTsInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vpvrRecTsInfo;
}
