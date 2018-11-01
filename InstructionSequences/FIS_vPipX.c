#include "libFireBird.h"

inline dword FIS_vPipX(void)
{
  TRACEENTER();

  static dword          _pipX = 0;

  if(!_pipX)
    _pipX = TryResolve("_pipX");

  TRACEEXIT();
  return _pipX;
}
