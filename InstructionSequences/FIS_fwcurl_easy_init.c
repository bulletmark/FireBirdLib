#include  "../libFireBird.h"

inline dword FIS_fwcurl_easy_init(void)
{
  static dword          _curl_easy_init = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_easy_init");
  #endif

  if(!_curl_easy_init)
    _curl_easy_init = TryResolve("curl_easy_init");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_easy_init;
}
