#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"

bool StrMkUTF8(byte *SourceString, size_t SourceSize, byte DefaultISO8859CharSet)
{
  TRACEENTER();

  char                 *_utf8string;
  bool                  result;

  if(!SourceString || !SourceSize)
  {
    TRACEEXIT();
    return FALSE;
  }

  _utf8string = TAP_MemAlloc(SourceSize << 2);

  if(!_utf8string)
  {
    TRACEEXIT();
    return FALSE;
  }

  memset(_utf8string, 0, SourceSize << 2);
  StrToUTF8(SourceString, _utf8string, DefaultISO8859CharSet);

  if (strlen(_utf8string) < SourceSize)
  {
    strcpy(SourceString, _utf8string);
    result = TRUE;
  }
  else result = FALSE;

  TAP_MemFree(_utf8string);

  TRACEEXIT();
  return result;
}
