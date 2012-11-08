#include                <string.h>
#include                "../libFireBird.h"

void StrToISO(byte *SourceString, byte *DestString)
{
  int                   Len;
  bool                  hasAnsiChars, hasUTFChars;

  if(!SourceString || !DestString) return;
  if(!*SourceString)
  {
    *DestString = '\0';
    return;
  }

  GetStringEncoding(SourceString, &hasAnsiChars, &hasUTFChars);

  if(!hasAnsiChars && hasUTFChars)
  {
    Len = strlen(SourceString);
    while(Len > 0)
    {
      *DestString = CharToISO(SourceString);
      if(isUTF8Char(SourceString))
      {
        SourceString++;
        Len--;
      }

      SourceString++;
      DestString++;
      Len--;
    }
    *DestString = '\0';
  }
  else
    strcpy(DestString, SourceString);
}
