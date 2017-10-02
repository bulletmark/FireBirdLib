#include                <string.h>
#include                "../libFireBird.h"

void StrToISO(byte *SourceString, byte *DestString)
{
  TRACEENTER();

  int                   Len;
  bool                  hasAnsiChars, hasUTFChars;
  byte                  BytesPerCharacter;
  dword                 UTF32;

  if(!SourceString || !DestString)
  {
    TRACEEXIT();
    return;
  }

  if(!*SourceString)
  {
    *DestString = '\0';

    TRACEEXIT();
    return;
  }

  GetStringEncoding(SourceString, &hasAnsiChars, &hasUTFChars);

  if(!hasAnsiChars && hasUTFChars)
  {
    Len = strlen(SourceString);
    while(Len > 0)
    {
      UTF32 = UTF8ToUTF32(SourceString, &BytesPerCharacter);

      if(UTF32 > 0xff)
      {
        //LogEntryFBLibPrintf(TRUE, "StrToISO: character 0x%4.4x ignored", UTF32);
      }
      else
      {
        *DestString = UTF32 & 0xff;
        DestString++;
      }

      SourceString += BytesPerCharacter;

      Len -= BytesPerCharacter;
    }
    *DestString = '\0';
  }
  else
    strcpy(DestString, SourceString);

  TRACEEXIT();
}
