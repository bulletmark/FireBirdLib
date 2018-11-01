#include "FBLib_ini.h"
#include "libFireBird.h"

char *LangGetStringDefault(dword StringID, char *DefaultString)
{
  TRACEENTER();

  char *ret = LangGetString(StringID);

  if((ret[0] == '\0') && DefaultString)
  {
    TRACEEXIT();
    return DefaultString;
  }

  TRACEEXIT();
  return ret;
}
