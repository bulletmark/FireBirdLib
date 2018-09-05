#include  "libFireBird.h"

ezxml_t ezxml_parse_str(char *s, size_t len)
{
  TRACEENTER;

	ezxml_t		(*__ezxml_parse_str)(char *, size_t);
	ezxml_t		ret = 0;

	__ezxml_parse_str = (void*)FIS_fwezxml_parse_str();
	if(__ezxml_parse_str)
	{
		//call the function
		ret = __ezxml_parse_str(s, len);
	}

  TRACEEXIT;
	return ret;
}
