#include                "../libFireBird.h"

void GetStringEncoding(char *Text, bool *hasAnsiChars, bool *hasUTFChars)
{
  byte           *p;

  //Check if the channel name contains UTF or ANSI characters
  if(hasAnsiChars) *hasAnsiChars = FALSE;
  if(hasUTFChars) *hasUTFChars = FALSE;
  if(!Text || !Text[0]) return;

  p = Text;
  while(*p)
  {
    if(*p >= 0x80)
    {
      if(isUTF8Char(p))
      {
        p++;
        if(hasUTFChars) *hasUTFChars = TRUE;
      }
      else
      {
        if(hasAnsiChars) *hasAnsiChars = TRUE;
      }
    }
    p++;
  }
}
