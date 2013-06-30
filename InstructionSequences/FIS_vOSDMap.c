#include "../libFireBird.h"

inline dword FIS_vOsdMap(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vOsdMap");
  #endif

  static dword          vOSDMap = 0;

  if(!vOSDMap)
    vOSDMap = TryResolve("_osdInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vOSDMap;
}
