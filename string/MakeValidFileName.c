#include <string.h>
#include "FBLib_string.h"

void MakeValidFileName(char *strName, eRemoveChars ControlCharacters)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("MakeValidFileName");
  #endif

  byte                  *s, *d;
  byte                  BytesPerCharacter;

  d = strName;
  s = strName;

  while(*s)
  {
    if(isLegalChar(s, ControlCharacters))
    {
      *d = *s;
      if(isUTF8Char(s, &BytesPerCharacter))
      {
        //As this is a multibyte UTF character, copy all bytes
        memcpy(d, s, BytesPerCharacter);
        d += BytesPerCharacter;
        s += (BytesPerCharacter - 1);
      }
      else
      {
        *d = *s;
        d++;
      }
    }
    s++;
  }
  *d = '\0';

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
