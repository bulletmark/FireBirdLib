#include "../libFireBird.h"

inline dword FIS_fwezxml_parse_str(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_parse_str");
  #endif

  static dword          _ezxml_parse_str = 0;

  if (!_ezxml_parse_str)
    _ezxml_parse_str = TryResolve("ezxml_parse_str");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_parse_str;
}
