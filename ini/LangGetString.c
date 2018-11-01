#include "FBLib_ini.h"
#include "libFireBird.h"

char *LangGetString(dword StringID)
{
  TRACEENTER();

  char *ret;

  if(!LangStrings || !LangStringPtr || (StringID >= LangNrStrings))
    ret = "";
  else
    ret = &LangStrings[LangStringPtr[StringID]];

  TRACEEXIT();
  return ret;
}
