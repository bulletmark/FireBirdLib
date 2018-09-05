#include                <ctype.h>
#include                <string.h>
#include                "FBLib_string.h"

void UpperCase(char *string)
{
  TRACEENTER;

  char                 *p, *s;
  byte                  UTF8[5];
  byte                  BytesPerCharacter;

  p = string;
  while(*p)
  {
    isUTF8Char(p, &BytesPerCharacter);
    if(BytesPerCharacter > 1)
    {
      memcpy(UTF8, p, BytesPerCharacter);
      UTF8[BytesPerCharacter] = '\0';
      s = strstr(UTF8Lower, UTF8);
      if(s) memcpy(p, &UTF8Upper[(dword)s - (dword)UTF8Lower], BytesPerCharacter);
    }
    else
    {
      s = strchr(AnsiLower, *p);
      if(s)
      {
        *p = AnsiUpper[(dword)s - (dword)AnsiLower];
      }
      else
        *p = toupper(*p);
    }

    p += BytesPerCharacter;
  }

  TRACEEXIT;
}
