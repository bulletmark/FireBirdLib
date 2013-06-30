#include "../libFireBird.h"

inline dword FIS_fwezxml_idx(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_idx");
  #endif

  static dword          _ezxml_idx = 0;

  if (!_ezxml_idx)
    _ezxml_idx = TryResolve("ezxml_idx");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_idx;
}
