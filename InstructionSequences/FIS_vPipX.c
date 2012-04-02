#include "../libFireBird.h"

inline dword FIS_vPipX(void)
{
  static dword          _pipX = 0;

  if (!_pipX)
    _pipX = TryResolve("_pipX");

  return _pipX;
}
