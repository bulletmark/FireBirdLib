#include  "libFireBird.h"

inline dword FIS_fwcurl_easy_init(void)
{
  static dword          _curl_easy_init = 0;

  TRACEENTER;

  if(!_curl_easy_init)
    _curl_easy_init = TryResolve("curl_easy_init");

  TRACEEXIT;
  return _curl_easy_init;
}
