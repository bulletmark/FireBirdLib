#include <string.h>
#include <stdlib.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_ini.h"
#include "../libFireBird.h"

long int INIGetInt(char *Key, long int DefaultValue, long int MinValue, long int MaxValue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetInt");
  #endif

  char                  *i = NULL, *j = NULL, *k;
  char                  TempKey[80];
  long int              l, x;

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

  INIFindStartEnd(TempKey, &i, &j, l + 11);   // max. digits for long int plus sign

  if(!i || !j || (j < i + l))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return DefaultValue;
  }

  for(k = i + l; k <= j; k++)
  {
    if(k == i + l && *k == '-' && k < j) continue;
    if(!isdigit(*k))
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return DefaultValue;
    }
  }

  x = strtoul(i + l, NULL, 10);

  if(x < MinValue) x = MinValue;
  if(x > MaxValue) x = MaxValue;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return x;
}
