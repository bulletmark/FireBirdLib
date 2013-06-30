#include "../libFireBird.h"

inline dword FIS_vShoutCastInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vShoutCastInfo");
  #endif

  static dword          _shoutCastInfo = 0;

  if(!_shoutCastInfo)
    _shoutCastInfo = TryResolve("_shoutCastInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _shoutCastInfo;
}
