#include                "libFireBird.h"

dword StringDBPrev(tStringDB *StringDB)
{
  TRACEENTER();

  char                 *p;
  dword                 ret;

  if(!StringDB || !StringDB->DBPtr || (StringDB->DBPtr <= StringDB->DB))
  {
    TRACEEXIT();
    return '\0';
  }

  p = (StringDB->DBPtr - 2);
  while(*p || (p >= StringDB->DB)) p--;
  p++;
  StringDB->DBPtr = p;
  ret = (dword)p - (dword)StringDB->DB;

  TRACEEXIT();
  return ret;
}
