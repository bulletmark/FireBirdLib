#include                <string.h>
#include                "../libFireBird.h"

bool StrMkISO(byte *SourceString)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StrMkISO");
  #endif

  byte                 *_isostring;
  bool                  hasAnsiChars, hasUTFChars;

  if(!SourceString)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(!*SourceString)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return FALSE;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
