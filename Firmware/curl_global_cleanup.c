#include "../libFireBird.h"

void curl_global_cleanup(void)
{
	//use the real prototype here
	void			(*__curl_global_cleanup)(void);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("curl_global_cleanup");
  #endif

	__curl_global_cleanup = (void*)FIS_fwcurl_global_cleanup();
	if(__curl_global_cleanup)
		__curl_global_cleanup();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
