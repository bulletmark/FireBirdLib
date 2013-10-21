#include "../libFireBird.h"

inline dword FIS_vPvrRecTempInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPvrRecTempInfo");
  #endif

  static dword          vpvrRecTempInfo = 0;

  if(!vpvrRecTempInfo)
    vpvrRecTempInfo = TryResolve("_pvrRecTempInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vpvrRecTempInfo;
}
