#include <string.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

bool INIKeyExists(char *Key)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIKeyExists");
  #endif

  char                  *i = NULL, *j = NULL;
  char                  TempKey[80];
  bool                  ret;

  if(Key && INIBuffer)
  {
    strncpy(TempKey, Key, sizeof(TempKey) - 2);
    TempKey[sizeof(TempKey) - 2] = '\0';
    strcat(TempKey, "=");

    INIFindStartEnd(TempKey, &i, &j, BufferSize);
    ret = (i && j);
  }
  else
    ret = FALSE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
