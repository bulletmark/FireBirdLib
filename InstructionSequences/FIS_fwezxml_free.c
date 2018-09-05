#include "libFireBird.h"

inline dword FIS_fwezxml_free(void)
{
  TRACEENTER;

  static dword          _ezxml_free = 0;

  if (!_ezxml_free)
    _ezxml_free = TryResolve("ezxml_free");

  TRACEEXIT;
  return _ezxml_free;
}
