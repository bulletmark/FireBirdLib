#include <string.h>
#include "FBLib_string.h"

void ReplaceInvalidFileNameChars(char *strName)
{
  unsigned char         *p, c;
  int                   i;
  int                   fileNameLength;

  p = strName;
  i = 0;
  fileNameLength = strlen(strName);
  while (i < fileNameLength)
  {
    c = strName[i];
    if(isLegalChar(c, InvalidFileNameChars))
    {
      *p = c;
    }
    else
    {
      switch (c)
      {
        // These characters are not allowed in Windows.
        case '*': *p = 'x'; break;
        case '"': *p = '\''; break;

        default:
          *p = '-';
          break;
      }
    }
    p++;
    i++;
  }
  *p = '\0';
}
