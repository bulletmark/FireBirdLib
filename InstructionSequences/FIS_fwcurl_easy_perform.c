#include  "../libFireBird.h"

inline dword FIS_fwcurl_easy_perform(void)
{
  static dword          _curl_easy_perform = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_easy_perform");
  #endif

  if(!_curl_easy_perform)
    _curl_easy_perform = TryResolve("curl_easy_perform");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_easy_perform;
}
