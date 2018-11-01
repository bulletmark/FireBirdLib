#include  "libFireBird.h"

inline dword FIS_fwcurl_easy_setopt(void)
{
  static dword          _curl_easy_setopt = 0;

  TRACEENTER();

  if(!_curl_easy_setopt)
    _curl_easy_setopt = TryResolve("curl_easy_setopt");

  TRACEEXIT();
  return _curl_easy_setopt;
}
