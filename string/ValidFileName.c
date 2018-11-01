#include <string.h>
#include "FBLib_string.h"

char *ValidFileName(char *strName, eRemoveChars ControlCharacters, char *Result, int ResultSize)
{
  TRACEENTER();

  char                  *s, *d, *l;
  byte                  BytesPerCharacter;

  d = Result;

  if(strName && *strName && Result && (ResultSize > (int)strlen(strName)))
  {
    strcpy(Result, strName);
    s = strName;
    l = d + MAX_FILE_NAME_SIZE - 1;

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
      if(d == l) break;
      s++;
    }
  }
  if(ResultSize) *d = '\0';

  TRACEEXIT();
  return Result;
}
