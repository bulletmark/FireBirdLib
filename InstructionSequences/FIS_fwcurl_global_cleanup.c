#include  "../libFireBird.h"

inline dword FIS_fwcurl_global_cleanup(void)
{
  static dword          _curl_global_cleanup = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_global_cleanup");
  #endif

  if(!_curl_global_cleanup)
    _curl_global_cleanup = TryResolve("curl_global_cleanup");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_global_cleanup;
}
