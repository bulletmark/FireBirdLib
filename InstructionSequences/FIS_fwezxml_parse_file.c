#include "../libFireBird.h"

inline dword FIS_fwezxml_parse_file(void)
{
  TRACEENTER();

  static dword          _ezxml_parse_file = 0;

  if (!_ezxml_parse_file)
    _ezxml_parse_file = TryResolve("ezxml_parse_file");

  TRACEEXIT();
  return _ezxml_parse_file;
}
