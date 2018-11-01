#include                "libFireBird.h"

char *StringDBGet(tStringDB *StringDB, dword Index)
{
  TRACEENTER();

  char *ret;

  if(!StringDB)
  {
    TRACEEXIT();
    return '\0';
  }

  ret = StringDB->DB + Index;

  TRACEEXIT();
  return ret;
}
