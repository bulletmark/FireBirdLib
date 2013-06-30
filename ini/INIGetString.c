#include <string.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

bool INIGetString(char *Key, char *Value, char *DefaultValue, dword MaxLength)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetString");
  #endif

  char                  *i = NULL, *j = NULL;
  char                  TempKey[80];
  dword                 l;

  if(!Key || !Value || !DefaultValue || !MaxLength)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");
  l = strlen(TempKey);

  INIFindStartEnd(TempKey, &i, &j, l + MaxLength);

  if(!i || !j || (j < i + l))
  {
    strncpy(Value, DefaultValue, MaxLength);
    Value[MaxLength - 1] = 0;
  }
  else
  {
    strncpy(Value, i + l, j - i - l + 1 );
    Value[j - i - l + 1] = 0;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
