#include                "../libFireBird.h"

void StrToISO(byte *SourceString, byte *DestString)
{
  if(!SourceString || !DestString) return;

  while(*SourceString)
  {
    *DestString = CharToISO(SourceString);
    if(isUTF8Char(SourceString)) SourceString++;
    SourceString++;
    DestString++;
  }
  *DestString = '\0';
}
