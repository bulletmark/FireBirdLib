#include "libFireBird.h"

inline dword FIS_vPipH(void)
{
  TRACEENTER();

  static dword          _pipH = 0;

  if(!_pipH)
    _pipH = TryResolve("_pipH");

  TRACEEXIT();
  return _pipH;
}
