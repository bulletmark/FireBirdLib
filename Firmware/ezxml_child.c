#include  "../libFireBird.h"

ezxml_t ezxml_child(ezxml_t xml, const char *name)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ezxml_child");
  #endif

	ezxml_t		(*__ezxml_child)(ezxml_t, const char *);
	ezxml_t		ret = 0;

	__ezxml_child = (void*)FIS_fwezxml_child();
	if(__ezxml_child)
	{
		//call the function
		ret = __ezxml_child(xml, name);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return ret;
}
