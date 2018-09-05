#include "libFireBird.h"

CURLcode curl_easy_perform(CURL *curl)
{
	//use the real prototype here
	CURLcode       (*__curl_easy_perform)(CURL *curl);
	CURLcode       result = 0;

  TRACEENTER;

	__curl_easy_perform = (void*)FIS_fwcurl_easy_perform();
	if(__curl_easy_perform)
		result = __curl_easy_perform(curl);

  TRACEEXIT;
	return result;
}
