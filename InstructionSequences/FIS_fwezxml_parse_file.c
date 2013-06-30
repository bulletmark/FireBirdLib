#include "../libFireBird.h"

inline dword FIS_fwezxml_parse_file(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwezxml_parse_file");
  #endif

  static dword          _ezxml_parse_file = 0;

  if (!_ezxml_parse_file)
    _ezxml_parse_file = TryResolve("ezxml_parse_file");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ezxml_parse_file;
}
