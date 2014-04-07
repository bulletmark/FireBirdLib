#include "../libFireBird.h"

inline dword FIS_fwezxml_parse_str(void)
{
  TRACEENTER();

  static dword          _ezxml_parse_str = 0;

  if (!_ezxml_parse_str)
    _ezxml_parse_str = TryResolve("ezxml_parse_str");

  TRACEEXIT();
  return _ezxml_parse_str;
}
