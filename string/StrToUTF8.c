#include                "../libFireBird.h"

void StrToUTF8(byte *SourceString, byte *DestString)
{
  dword                 c;

  if(!SourceString || !DestString) return;

  while(*SourceString)
  {
    if(*SourceString > 0x7f)
    {
      c = CharToUTF8(SourceString);
      *DestString = c >> 8;
      DestString++;
      *DestString = c & 0xff;
    }
    else
    {
      *DestString = *SourceString;
    }
    SourceString++;
    DestString++;
  }
  *DestString = '\0';
}
