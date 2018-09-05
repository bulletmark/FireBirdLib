#include "libFireBird.h"

void curl_easy_cleanup(CURL *curl)
{
	//use the real prototype here
	void			(*__curl_easy_cleanup)(CURL *curl);

  TRACEENTER;

	__curl_easy_cleanup = (void*)FIS_fwcurl_easy_cleanup();
	if(__curl_easy_cleanup)
		__curl_easy_cleanup(curl);

  TRACEEXIT;
}
