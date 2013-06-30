#include  "../libFireBird.h"

const char *ezxml_error(ezxml_t xml)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ezxml_error");
  #endif

	const char *(*__ezxml_error)(ezxml_t);
	const char *ret = NULL;

	__ezxml_error = (void*)FIS_fwezxml_error();
	if(__ezxml_error)
	{
		//call the function
		ret = __ezxml_error(xml);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return ret;
}
