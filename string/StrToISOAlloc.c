#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"

#undef malloc
#undef free

void StrToISOAlloc(byte *SourceString, byte **DestString)
{
  TRACEENTER();

  if((SourceString == NULL) || (DestString == NULL))
  {
    if(DestString) *DestString =  NULL;

    TRACEEXIT();
    return;
  }

  *DestString = malloc(strlenUC(SourceString) + 1);
  StrToISO(SourceString, *DestString);

  TRACEEXIT();
}
