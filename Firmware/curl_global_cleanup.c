#include "libFireBird.h"

void curl_global_cleanup(void)
{
	//use the real prototype here
	void			(*__curl_global_cleanup)(void);

  TRACEENTER;

	__curl_global_cleanup = (void*)FIS_fwcurl_global_cleanup();
	if(__curl_global_cleanup)
		__curl_global_cleanup();

  TRACEEXIT;
}
