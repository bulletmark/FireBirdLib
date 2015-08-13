#include <stdlib.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

void LangUnloadStrings(void)
{
  TRACEENTER();

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

  TRACEEXIT();
}
