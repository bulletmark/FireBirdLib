#include "libFireBird.h"

inline dword FIS_fwezxml_idx(void)
{
  TRACEENTER();

  static dword          _ezxml_idx = 0;

  if (!_ezxml_idx)
    _ezxml_idx = TryResolve("ezxml_idx");

  TRACEEXIT();
  return _ezxml_idx;
}
