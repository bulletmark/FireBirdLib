#include                <string.h>
#include                "../libFireBird.h"

bool StrMkISO(byte *SourceString)
{
  char                 *_isostring;
  int                   Len;
  bool                  hasAnsiChars, hasUTFChars;

  if(!SourceString) return FALSE;
  if(!*SourceString) return TRUE;

  GetStringEncoding(SourceString, &hasAnsiChars, &hasUTFChars);

  if(!hasAnsiChars && hasUTFChars)
  {
    Len = strlen(SourceString);
    _isostring = TAP_MemAlloc(Len + 1);
    if(!_isostring) return FALSE;

    memset(_isostring, 0, Len + 1);
    StrToISO(SourceString, _isostring);
    memcpy(SourceString, _isostring, Len + 1);
    TAP_MemFree(_isostring);
  }

  return TRUE;
}
