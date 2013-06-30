#include "../libFireBird.h"

inline dword FIS_vciplusMenuMode(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vciplusMenuMode");
  #endif

  static dword          vciplusMenuMode = 0;

  if(!vciplusMenuMode)
    vciplusMenuMode = TryResolve("_ciplusMenuMode");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vciplusMenuMode;
}
