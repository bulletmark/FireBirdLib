#include "../libFireBird.h"

CURLcode curl_easy_perform(CURL *curl)
{
	//use the real prototype here
	CURLcode       (*__curl_easy_perform)(CURL *curl);
	CURLcode       result = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("curl_easy_perform");
  #endif

	__curl_easy_perform = (void*)FIS_fwcurl_easy_perform();
	if(__curl_easy_perform)
		result = __curl_easy_perform(curl);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return result;
}
