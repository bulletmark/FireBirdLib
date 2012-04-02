#include "../libFireBird.h"

inline dword FIS_vShoutCastInfo(void)
{
  static dword          _shoutCastInfo = 0;

  if (!_shoutCastInfo)
    _shoutCastInfo = TryResolve("_shoutCastInfo");

  return _shoutCastInfo;
}
