#include                <string.h>
#include                "../libFireBird.h"

bool StrMkUTF8(byte *SourceString)
{
  char                   *_utf8string;

  if(!SourceString) return FALSE;

  _utf8string = TAP_MemAlloc(strlen(SourceString) << 1);
  if(!_utf8string) return FALSE;

  StrToUTF8(SourceString, _utf8string);
  strcpy(SourceString, _utf8string);
  TAP_MemFree(_utf8string);

  return TRUE;
}
