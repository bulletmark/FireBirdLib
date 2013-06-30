#include "../libFireBird.h"

inline dword FIS_fwezxml_attr(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_attr");
  #endif

  static dword          _ezxml_attr = 0;

  if (!_ezxml_attr)
    _ezxml_attr = TryResolve("ezxml_attr");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_attr;
}
