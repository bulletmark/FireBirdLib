#include                <string.h>
#include                "../libFireBird.h"

int strlenUC(byte *s)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("strlenUC");
  #endif

  byte                 *p, *pEnd;
  int                   Count;
  byte                  BPC;

  if(!s || !*s)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  p = SkipCharTableBytes(s);
  pEnd = p + strlen(p);

  Count = 0;
  while(p < pEnd)
  {
    isUTF8Char(p, &BPC);
    Count++;
    p += BPC;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Count;
}
