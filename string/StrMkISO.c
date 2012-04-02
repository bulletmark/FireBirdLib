#include                <string.h>
#include                "../libFireBird.h"

bool StrMkISO(byte *SourceString)
{
  char                 *_isostring;

  if(!SourceString) return FALSE;

  _isostring = TAP_MemAlloc(strlen(SourceString));
  if(!_isostring) return FALSE;

  StrToISO(SourceString, _isostring);
  strcpy(SourceString, _isostring);
  TAP_MemFree(_isostring);

  return TRUE;
}
