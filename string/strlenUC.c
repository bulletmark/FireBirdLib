#include                <string.h>
#include                "libFireBird.h"

int strlenUC(byte *s)
{
  TRACEENTER;

  byte                 *p, *pEnd;
  int                   Count;
  byte                  BPC;

  if(!s || !*s)
  {
    TRACEEXIT;
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

  TRACEEXIT;
  return Count;
}
