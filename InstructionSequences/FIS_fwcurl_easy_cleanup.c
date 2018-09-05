#include  "libFireBird.h"

inline dword FIS_fwcurl_easy_cleanup(void)
{
  static dword          _curl_easy_cleanup = 0;

  TRACEENTER;

  if(!_curl_easy_cleanup)
    _curl_easy_cleanup = TryResolve("curl_easy_cleanup");

  TRACEEXIT;
  return _curl_easy_cleanup;
}
