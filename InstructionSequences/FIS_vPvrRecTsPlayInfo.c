#include "../libFireBird.h"

inline dword FIS_vPvrRecTsPlayInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPvrRecTsPlayInfo");
  #endif

  static dword          vpvrRecTsPlayInfo = 0;

  if(!vpvrRecTsPlayInfo)
    vpvrRecTsPlayInfo = TryResolve("_pvrRecTsPlayInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vpvrRecTsPlayInfo;
}
