#include <string.h>
#include <stdlib.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_ini.h"
#include "../libFireBird.h"

word INIGetHexWord(char *Key, word DefaultValue, word MinValue, word MaxValue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetHexWord");
  #endif

  char                  *i = NULL, *j = NULL, *k;
  char                  TempKey[80];
  dword                 l, x;

  if(!Key)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");
  l = strlen(TempKey);

  INIFindStartEnd(TempKey, &i, &j, l + sizeof(word) * 2);

  if(!i || !j || (j < i + l))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return DefaultValue;
  }

  for(k = i + l; k <= j; k++)
    if(!isxdigit(*k))
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return DefaultValue;
    }

  x = (word) strtoul(i + l, NULL, 16);

  if(x < MinValue) x = MinValue;
  if(x > MaxValue) x = MaxValue;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return x;
}
