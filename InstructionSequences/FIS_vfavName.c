#include "../libFireBird.h"

inline dword FIS_vfavName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vfavName");
  #endif

  static dword          vfavName = 0;

  if(!vfavName)
    vfavName = TryResolve("_favName");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vfavName;
}
