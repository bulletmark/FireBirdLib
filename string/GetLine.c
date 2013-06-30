#include <string.h>
#include "../libFireBird.h"

size_t GetLine(char *data, bool strip)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetLine");
  #endif

  char                  *CRLFPos, *LFPos;

  if(!*data)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  CRLFPos = strstr(data, "\r\n");
  LFPos = strchr(data, '\n');

  if(CRLFPos == NULL && LFPos == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return strlen(data);
  }
  else if(CRLFPos == NULL || LFPos < CRLFPos)
  {
    if(strip) *LFPos = '\0';
    size_t ret = LFPos - data + 1;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return ret;
  }
  else
  {
    if(strip) *CRLFPos = '\0';

    size_t ret = CRLFPos - data + 2;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return ret;
  }
}
