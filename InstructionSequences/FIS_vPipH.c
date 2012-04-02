#include "../libFireBird.h"

inline dword FIS_vPipH(void)
{
  static dword          _pipH = 0;

  if (!_pipH)
    _pipH = TryResolve("_pipH");

  return _pipH;
}
