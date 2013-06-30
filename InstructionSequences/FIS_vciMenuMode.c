#include "../libFireBird.h"

inline dword FIS_vciMenuMode(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vciMenuMode");
  #endif

  static dword          vciMenuMode = 0;

  if(!vciMenuMode)
    vciMenuMode = TryResolve("_ciMenuMode");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vciMenuMode;
}
