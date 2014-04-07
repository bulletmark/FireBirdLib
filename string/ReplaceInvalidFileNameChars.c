#include <string.h>
#include "FBLib_string.h"

void ReplaceInvalidFileNameChars(char *strName)
{
  TRACEENTER();

  unsigned char         *s, *d;

  s = SkipCharTableBytes(strName);
  d = s;

  while(*s)
  {
    if(isLegalChar(s, InvalidFileNameChars))
    {
      *d = *s;
    }
    else
    {
      switch(*s)
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

  TRACEEXIT();
}
