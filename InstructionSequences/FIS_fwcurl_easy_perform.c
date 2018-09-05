#include  "libFireBird.h"

inline dword FIS_fwcurl_easy_perform(void)
{
  static dword          _curl_easy_perform = 0;

  TRACEENTER;

  if(!_curl_easy_perform)
    _curl_easy_perform = TryResolve("curl_easy_perform");

  TRACEEXIT;
  return _curl_easy_perform;
}
