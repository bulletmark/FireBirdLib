#include "../libFireBird.h"

CURLcode curl_global_init(long flags)
{
	//use the real prototype here
	CURLcode        (*__curl_global_init)(long);
	CURLcode			result = CURLE_FAILED_INIT;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("curl_global_init");
  #endif

	__curl_global_init = (void*)FIS_fwcurl_global_init();
	if(__curl_global_init)
	{
		//call the function
		result = __curl_global_init(flags);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return result;
}
