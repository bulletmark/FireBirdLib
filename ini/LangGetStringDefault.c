#include "FBLib_ini.h"
#include "../libFireBird.h"

char *LangGetStringDefault(dword StringID, char *DefaultString)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LangGetStringDefault");
  #endif

  char *ret = LangGetString(StringID);

  if((ret[0] == '\0') && DefaultString)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return DefaultString;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
