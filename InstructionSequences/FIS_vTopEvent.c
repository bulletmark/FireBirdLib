#include "../libFireBird.h"

inline dword FIS_vTopEvent(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTopEvent");
  #endif

  static dword          vtopEvent = 0;

  if(!vtopEvent)
    vtopEvent = TryResolve("_topEvent");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vtopEvent;
}
