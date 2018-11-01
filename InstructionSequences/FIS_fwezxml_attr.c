#include "libFireBird.h"

inline dword FIS_fwezxml_attr(void)
{
  TRACEENTER();

  static dword          _ezxml_attr = 0;

  if (!_ezxml_attr)
    _ezxml_attr = TryResolve("ezxml_attr");

  TRACEEXIT();
  return _ezxml_attr;
}
