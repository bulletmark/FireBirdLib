#include  "../libFireBird.h"

ezxml_t ezxml_idx(ezxml_t xml, int idx)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ezxml_idx");
  #endif

	ezxml_t		(*__ezxml_idx)(ezxml_t, int);
	ezxml_t		ret = 0;

	__ezxml_idx = (void*)FIS_fwezxml_idx();
	if(__ezxml_idx)
	{
		//call the function
		ret = __ezxml_idx(xml, idx);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

	return ret;
}
