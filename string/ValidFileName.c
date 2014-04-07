#include "FBLib_string.h"

char *ValidFileName(char *strName, eRemoveChars ControlCharacters)
{
  TRACEENTER();

  char                  *s, *d, *l;
  byte                  BytesPerCharacter;
  static char           validName[FBLIB_DIR_SIZE];

  d = validName;

  if(strName && *strName)
  {
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
  *d = '\0';

  TRACEEXIT();
  return validName;
}
