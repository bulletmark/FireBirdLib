#include "../libFireBird.h"

inline dword FIS_vCheckAutoDecTimerId(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vCheckAutoDecTimerId");
  #endif

  static dword          _checkAutoDecTimerId = 0;

  if(!_checkAutoDecTimerId)
    _checkAutoDecTimerId = TryResolve("_checkAutoDecTimerId");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _checkAutoDecTimerId;
}
