#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"

bool StrMkISO(byte *SourceString)
{
  TRACEENTER();

  byte                 *_isostring;
  bool                  hasAnsiChars, hasUTFChars;

  if(!SourceString)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!*SourceString)
  {
    TRACEEXIT();
    return TRUE;
  }

  GetStringEncoding(SourceString, &hasAnsiChars, &hasUTFChars);

  if(!hasAnsiChars && hasUTFChars)
  {
    StrToISOAlloc(SourceString, &_isostring);
    if(_isostring)
    {
      strcpy(SourceString, _isostring);
      TAP_MemFree(_isostring);
    }
    else
    {
      TRACEEXIT();
      return FALSE;
    }
  }

  TRACEEXIT();
  return TRUE;
}
