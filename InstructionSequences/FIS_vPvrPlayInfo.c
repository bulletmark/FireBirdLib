#include "../libFireBird.h"

inline dword FIS_vPvrPlayInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPvrPlayInfo");
  #endif

  static dword          vPvrPlayInfo = 0;

  if(!vPvrPlayInfo)
    vPvrPlayInfo = TryResolve("_pvrPlayInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vPvrPlayInfo;
}
