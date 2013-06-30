#include  "../libFireBird.h"

const char *ezxml_attr(ezxml_t xml, const char *attr)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ezxml_attr");
  #endif

	const char *(*__ezxml_attr)(ezxml_t, const char *);
	const char *ret = NULL;

	__ezxml_attr = (void*)FIS_fwezxml_attr();
	if(__ezxml_attr)
	{
		//call the function
		ret = __ezxml_attr(xml, attr);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return ret;
}
