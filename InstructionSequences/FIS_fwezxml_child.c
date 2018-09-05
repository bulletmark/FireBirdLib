#include "libFireBird.h"

inline dword FIS_fwezxml_child(void)
{
  TRACEENTER;

  static dword          _ezxml_child = 0;

  if (!_ezxml_child)
    _ezxml_child = TryResolve("ezxml_child");

  TRACEEXIT;
  return _ezxml_child;
}
