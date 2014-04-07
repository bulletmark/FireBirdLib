#include "../libFireBird.h"

inline dword FIS_fwezxml_error(void)
{
  TRACEENTER();

  static dword          _ezxml_error = 0;

  if (!_ezxml_error)
    _ezxml_error = TryResolve("ezxml_error");

  TRACEEXIT();
  return _ezxml_error;
}
