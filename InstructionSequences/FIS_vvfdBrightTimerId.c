#include "../libFireBird.h"

inline dword FIS_vVfdBrightTimerId(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vVfdBrightTimerId");
  #endif

  static dword          _vfdBrightTimerId = 0;

  if(!_vfdBrightTimerId)
    _vfdBrightTimerId = TryResolve("_vfdBrightTimerId");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _vfdBrightTimerId;
}
