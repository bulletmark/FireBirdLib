#include "FBLib_ini.h"
#include "../libFireBird.h"

char *LangGetStringDefault(dword StringID, char *DefaultString)
{
  char *ret;

  ret = LangGetString(StringID);

  if((ret[0] == '\0') && DefaultString) return DefaultString;

  return ret;
}
