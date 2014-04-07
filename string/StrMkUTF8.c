#include                <string.h>
#include                "../libFireBird.h"

bool StrMkUTF8(byte *SourceString, byte DefaultISO8859CharSet)
{
  TRACEENTER();

  char                 *_utf8string;
  int                   l;

  if(!SourceString)
  {
    TRACEEXIT();
    return FALSE;
  }

  l = strlen(SkipCharTableBytes(SourceString)) << 2;
  if(l == 0)
  {
    *SourceString = '\0';

    TRACEEXIT();
    return TRUE;
  }

  _utf8string = TAP_MemAlloc(l);
  if(!_utf8string)
  {
    TRACEEXIT();
    return FALSE;
  }

  StrToUTF8(SourceString, _utf8string, DefaultISO8859CharSet);
  strcpy(SourceString, _utf8string);
  TAP_MemFree(_utf8string);

  TRACEEXIT();
  return TRUE;
}
