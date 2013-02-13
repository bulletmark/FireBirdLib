#include <string.h>
#include "FBLib_string.h"

void MakeValidFileName(char *strName, eRemoveChars ControlCharacters)
{
  unsigned char         *s, *d;

  d = strName;
  s = strName;

  while(*s)
  {
    if(isLegalChar(s, ControlCharacters))
    {
      *d = *s;
      if(isUTF8Char(s))
      {
        //As this is a double byte UTF character, copy both bytes
        d++;
        s++;
        *d = *s;
      }
      d++;
    }
    s++;
  }
  *d = '\0';
}
