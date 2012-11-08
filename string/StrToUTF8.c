#include                <string.h>
#include                "../libFireBird.h"

void StrToUTF8(byte *SourceString, byte *DestString)
{
  dword                 c;
  bool                  hasAnsiChars, hasUTFChars;

  if(!SourceString || !DestString) return;

  GetStringEncoding(SourceString, &hasAnsiChars, &hasUTFChars);

  if(hasAnsiChars && !hasUTFChars)
  {
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
  else
    strcpy(DestString, SourceString);
}
