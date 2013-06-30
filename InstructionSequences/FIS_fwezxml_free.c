#include "../libFireBird.h"

inline dword FIS_fwezxml_free(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_free");
  #endif

  static dword          _ezxml_free = 0;

  if (!_ezxml_free)
    _ezxml_free = TryResolve("ezxml_free");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_free;
}
