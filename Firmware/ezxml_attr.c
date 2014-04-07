#include  "../libFireBird.h"

const char *ezxml_attr(ezxml_t xml, const char *attr)
{
  TRACEENTER();

	const char *(*__ezxml_attr)(ezxml_t, const char *);
	const char *ret = NULL;

	__ezxml_attr = (void*)FIS_fwezxml_attr();
	if(__ezxml_attr)
	{
		//call the function
		ret = __ezxml_attr(xml, attr);
	}

  TRACEEXIT();
	return ret;
}
