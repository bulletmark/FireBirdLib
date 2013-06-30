#include "../libFireBird.h"

void curl_easy_cleanup(CURL *curl)
{
	//use the real prototype here
	void			(*__curl_easy_cleanup)(CURL *curl);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("curl_easy_cleanup");
  #endif

	__curl_easy_cleanup = (void*)FIS_fwcurl_easy_cleanup();
	if(__curl_easy_cleanup)
		__curl_easy_cleanup(curl);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
