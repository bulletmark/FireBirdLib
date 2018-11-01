#include                "libFireBird.h"

dword StringDBFirst(tStringDB *StringDB)
{
  TRACEENTER();

  dword ret;

  if(!StringDB)
  {
    TRACEEXIT();
    return '\0';
  }

  StringDB->DBPtr = StringDB->DB;
  ret = (dword)StringDB->DBPtr - (dword)StringDB->DB;

  TRACEEXIT();
  return ret;
}
