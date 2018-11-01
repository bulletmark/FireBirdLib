#include  "libFireBird.h"

const char *ezxml_error(ezxml_t xml)
{
  TRACEENTER();

	const char *(*__ezxml_error)(ezxml_t);
	const char *ret = NULL;

	__ezxml_error = (void*)FIS_fwezxml_error();
	if(__ezxml_error)
	{
		//call the function
		ret = __ezxml_error(xml);
	}

  TRACEEXIT();
	return ret;
}
