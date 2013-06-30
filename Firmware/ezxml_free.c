#include  "../libFireBird.h"

void ezxml_free(ezxml_t xml)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ezxml_free");
  #endif

	void		(*__ezxml_free)(ezxml_t);

	__ezxml_free = (void*)FIS_fwezxml_free();
	if(__ezxml_free)
	{
		//call the function
		__ezxml_free(xml);
	}

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
