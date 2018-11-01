#include  "libFireBird.h"

inline dword FIS_fwcurl_global_init(void)
{
  static dword          _curl_global_init = 0;

  TRACEENTER();

  if(!_curl_global_init)
    _curl_global_init = TryResolve("curl_global_init");

  TRACEEXIT();
  return _curl_global_init;
}
