#include  "../libFireBird.h"

inline dword FIS_fwcurl_easy_setopt(void)
{
  static dword          _curl_easy_setopt = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_easy_setopt");
  #endif

  if(!_curl_easy_setopt)
    _curl_easy_setopt = TryResolve("curl_easy_setopt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_easy_setopt;
}
