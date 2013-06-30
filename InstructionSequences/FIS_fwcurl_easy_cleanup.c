#include  "../libFireBird.h"

inline dword FIS_fwcurl_easy_cleanup(void)
{
  static dword          _curl_easy_cleanup = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_easy_cleanup");
  #endif

  if(!_curl_easy_cleanup)
    _curl_easy_cleanup = TryResolve("curl_easy_cleanup");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_easy_cleanup;
}
