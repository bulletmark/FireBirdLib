#include                "libFireBird.h"

bool StringDBEOF(tStringDB *StringDB)
{
  TRACEENTER();

  bool ret;

  if(!StringDB)
  {
    TRACEEXIT();
    return TRUE;
  }
  ret = (StringDB->DBPtr[0] == '\0');

  TRACEEXIT();
  return ret;
}
