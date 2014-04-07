#include "../libFireBird.h"

inline dword FIS_vShoutCastInfo(void)
{
  TRACEENTER();

  static dword          _shoutCastInfo = 0;

  if(!_shoutCastInfo)
    _shoutCastInfo = TryResolve("_shoutCastInfo");

  TRACEEXIT();
  return _shoutCastInfo;
}
