#include "../libFireBird.h"

CURL *curl_easy_init(void)
{
	//use the real prototype here
	CURL*                 (*__curl_easy_init)(void);
	CURL*                 handle = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("curl_easy_init");
  #endif

	__curl_easy_init = (void*)FIS_fwcurl_easy_init();
	if(__curl_easy_init)
		handle = __curl_easy_init();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return handle;
}
