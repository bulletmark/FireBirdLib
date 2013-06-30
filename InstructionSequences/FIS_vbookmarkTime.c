#include "../libFireBird.h"

inline dword FIS_vbookmarkTime(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vbookmarkTime");
  #endif

  static dword          vbookmarkTime = 0;

  if(!vbookmarkTime)
    vbookmarkTime = TryResolve("_bookmarkTime");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vbookmarkTime;
}
