#include "FBLib_ini.h"
#include "../libFireBird.h"

char *LangGetString(dword StringID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LangGetString");
  #endif

  char *ret;

  if(!LangStrings || !LangStringPtr || (StringID >= LangNrStrings))
    ret = "";
  else
    ret = &LangStrings[LangStringPtr[StringID]];

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
