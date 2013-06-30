#include  "../libFireBird.h"

inline dword FIS_fwcurl_global_init(void)
{
  static dword          _curl_global_init = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwcurl_global_init");
  #endif

  if(!_curl_global_init)
    _curl_global_init = TryResolve("curl_global_init");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _curl_global_init;
}
