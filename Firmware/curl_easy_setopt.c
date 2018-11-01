#include "libFireBird.h"

CURLcode curl_easy_setopt(CURL *curl, CURLoption option, void *arg)
{
	//use the real prototype here
	CURLcode       (*__curl_easy_setopt)(CURL *, CURLoption, void *);
	CURLcode       result = 0;

  TRACEENTER();

	__curl_easy_setopt = (void*)FIS_fwcurl_easy_setopt();
	if(__curl_easy_setopt)
	{
		result = __curl_easy_setopt(curl, option, arg);
	}

  TRACEEXIT();
	return result;
}
