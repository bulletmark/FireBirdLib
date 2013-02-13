#include <string.h>
#include "FBLib_string.h"

void ReplaceInvalidFileNameChars(char *strName)
{
  unsigned char         *s, *d;

  d = strName;
  s = strName;
  while(*s)
  {
    if(isLegalChar(s, InvalidFileNameChars))
    {
      *d = *s;
    }
    else
    {
      switch (*s)
      {
        // These characters are not allowed in Windows.
        case '*': *d = 'x'; break;
        case '"': *d = '\''; break;

        default:
          *d = '-';
          break;
      }
    }
    d++;
    s++;
  }
  *d = '\0';
}
