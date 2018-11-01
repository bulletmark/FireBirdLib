#include <string.h>
#include "libFireBird.h"

size_t GetLine(char *data, bool strip)
{
  TRACEENTER();

  char                  *CRLFPos, *LFPos;

  if(!*data)
  {
    TRACEEXIT();
    return 0;
  }

  CRLFPos = strstr(data, "\r\n");
  LFPos = strchr(data, '\n');

  if(CRLFPos == NULL && LFPos == NULL)
  {
    TRACEEXIT();
    return strlen(data);
  }
  else if(CRLFPos == NULL || LFPos < CRLFPos)
  {
    if(strip) *LFPos = '\0';
    size_t ret = LFPos - data + 1;

    TRACEEXIT();
    return ret;
  }
  else
  {
    if(strip) *CRLFPos = '\0';

    size_t ret = CRLFPos - data + 2;

    TRACEEXIT();
    return ret;
  }
}
