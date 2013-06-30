#ifndef _TMSEMU_
  #include              <ctype.h>
#endif
#include                <string.h>
#include                "FBLib_string.h"

void UpperCase(char *string)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("UpperCase");
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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
