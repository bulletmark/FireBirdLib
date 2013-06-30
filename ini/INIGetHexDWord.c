#include <string.h>
#include <stdlib.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_ini.h"
#include "../libFireBird.h"

dword INIGetHexDWord(char *Key, dword DefaultValue, dword MinValue, dword MaxValue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetHexDWord");
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

  INIFindStartEnd(TempKey, &i, &j, l + sizeof(dword) * 2);

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

  x = (dword) strtoul(i + l, NULL, 16);

  if(x < MinValue) x = MinValue;
  if(x > MaxValue) x = MaxValue;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return x;
}
