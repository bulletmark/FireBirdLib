#include  "libFireBird.h"

inline dword FIS_fwcurl_global_cleanup(void)
{
  static dword          _curl_global_cleanup = 0;

  TRACEENTER;

  if(!_curl_global_cleanup)
    _curl_global_cleanup = TryResolve("curl_global_cleanup");

  TRACEEXIT;
  return _curl_global_cleanup;
}
