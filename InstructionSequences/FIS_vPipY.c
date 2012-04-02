#include "../libFireBird.h"

inline dword FIS_vPipY(void)
{
  static dword          _pipY = 0;

  if (!_pipY)
    _pipY = TryResolve("_pipY");

  return _pipY;
}
