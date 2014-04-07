#include  "../libFireBird.h"

ezxml_t ezxml_child(ezxml_t xml, const char *name)
{
  TRACEENTER();

	ezxml_t		(*__ezxml_child)(ezxml_t, const char *);
	ezxml_t		ret = 0;

	__ezxml_child = (void*)FIS_fwezxml_child();
	if(__ezxml_child)
	{
		//call the function
		ret = __ezxml_child(xml, name);
	}

  TRACEEXIT();
	return ret;
}
