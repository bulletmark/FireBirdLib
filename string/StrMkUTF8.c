#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"

bool StrMkUTF8(byte *SourceString, byte DefaultISO8859CharSet)
{
  TRACEENTER();

  char                 *_utf8string, *pEOS;
  int                   l;

  if(!SourceString)
  {
    TRACEEXIT();
    return FALSE;
  }

  //To handle UTF32 strings correctly, SourceString need to be terminated by 4 NULL bytes
  pEOS = SourceString;
  while(pEOS[0] || pEOS[1] || pEOS[2] || pEOS[3])
    pEOS++;

  l = ((dword)pEOS - (dword)SourceString) << 2;
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

  memset(_utf8string, 0, l);
  StrToUTF8(SourceString, _utf8string, DefaultISO8859CharSet);
  strcpy(SourceString, _utf8string);
  TAP_MemFree(_utf8string);

  TRACEEXIT();
  return TRUE;
}
