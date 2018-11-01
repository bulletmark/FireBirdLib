#include "libFireBird.h"

inline dword FIS_vPipW(void)
{
  TRACEENTER();

  static dword          _pipW = 0;

  if(!_pipW)
    _pipW = TryResolve("_pipW");

  TRACEEXIT();
  return _pipW;
}
