#include "FBLib_ini.h"
#include "../libFireBird.h"

void LangUnloadStrings(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LangUnloadStrings");
  #endif

  if(LangStrings)
  {
    TAP_MemFree(LangStrings);
    LangStrings = NULL;
  }

  if(LangStringPtr)
  {
    TAP_MemFree(LangStringPtr);
    LangStringPtr = NULL;
  }

  LangNrStrings = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
