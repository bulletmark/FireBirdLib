#include  "../libFireBird.h"

ezxml_t ezxml_parse_file(const char *file)
{
  TRACEENTER();

	ezxml_t		(*__ezxml_parse_file)(const char *);
	ezxml_t		ret = 0;

	__ezxml_parse_file = (void*)FIS_fwezxml_parse_file();
	if(__ezxml_parse_file)
	{
		//call the function
		ret = __ezxml_parse_file(file);
	}

  TRACEEXIT();
	return ret;
}
