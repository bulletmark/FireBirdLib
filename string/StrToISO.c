#include                <string.h>
#include                "../libFireBird.h"

void StrToISO(byte *SourceString, byte *DestString)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StrToISO");
  #endif

  int                   Len;
  bool                  hasAnsiChars, hasUTFChars;
  byte                  BytesPerCharacter;
  dword                 UTF32;

  if(!SourceString || !DestString)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  if(!*SourceString)
  {
    *DestString = '\0';

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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
        LogEntryFBLibPrintf(TRUE, "StrToISO: character 0x%4.4x ignored", UTF32);
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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
