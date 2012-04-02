#include "../libFireBird.h"

inline dword FIS_vIsPipActive(void)
{
  static dword          _isPipActive = 0;

  if (!_isPipActive)
    _isPipActive = TryResolve("_isPipActive");

  return _isPipActive;
}
