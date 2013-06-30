#include "../libFireBird.h"

inline dword FIS_fwezxml_error(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_error");
  #endif

  static dword          _ezxml_error = 0;

  if (!_ezxml_error)
    _ezxml_error = TryResolve("ezxml_error");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_error;
}
