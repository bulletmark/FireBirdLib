#include                <string.h>
#include                "libFireBird.h"

void GetStringEncoding(char *Text, bool *hasAnsiChars, bool *hasUTFChars)
{
  TRACEENTER;

  byte           *p, *pEnd;
  byte            BytesPerChar;
  bool            AC, UC;

  AC = FALSE;
  UC = FALSE;
  if(Text && Text[0])
  {
    p = SkipCharTableBytes(Text);
    pEnd = p + strlen(p);

    while(p < pEnd)
    {
      UC |= isUTF8Char(p, &BytesPerChar);
      if((*p >= 0xa0) && (BytesPerChar == 1)) AC = TRUE;
      p += BytesPerChar;
    }
  }

  if(hasAnsiChars) *hasAnsiChars = AC;
  if(hasUTFChars) *hasUTFChars = UC;

  TRACEEXIT;
}
