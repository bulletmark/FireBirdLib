#include <stdlib.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

#undef malloc
#undef free

void LangUnloadStrings(void)
{
  TRACEENTER();

  if(LangStrings)
  {
    free(LangStrings);
    LangStrings = NULL;
  }

  if(LangStringPtr)
  {
    free(LangStringPtr);
    LangStringPtr = NULL;
  }

  LangNrStrings = 0;

  TRACEEXIT();
}
