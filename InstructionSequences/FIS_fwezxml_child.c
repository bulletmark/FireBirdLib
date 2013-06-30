#include "../libFireBird.h"

inline dword FIS_fwezxml_child(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_child");
  #endif

  static dword          _ezxml_child = 0;

  if (!_ezxml_child)
    _ezxml_child = TryResolve("ezxml_child");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_child;
}
