#ifndef _TMSEMU_
  #include              <ctype.h>
#endif
#include                <string.h>
#include                "FBLib_string.h"

void LowerCase(char *string)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LowerCase");
  #endif

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
      s = strstr(UTF8Upper, UTF8);
      if(s) memcpy(p, &UTF8Lower[(dword)s - (dword)UTF8Upper], BytesPerCharacter);
    }
    else
    {
      s = strchr(AnsiUpper, *p);
      if(s)
      {
        *p = AnsiLower[(dword)s - (dword)AnsiUpper];
      }
      else
      {
        *p = tolower(*p);
      }
    }

    p += BytesPerCharacter;

  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
