#include                "../libFireBird.h"

dword StringDBNext(tStringDB *StringDB)
{
  TRACEENTER();

  char                 *p;
  dword                 ret;

  if(!StringDB || !StringDB->DBPtr || (StringDB->DBPtr >= StringDB->DBEnd))
  {
    TRACEEXIT();
    return '\0';
  }

  p = StringDB->DBPtr;
  while(*p) p++;
  p++;
  StringDB->DBPtr = p;
  ret = (dword)p - (dword)StringDB->DB;

  TRACEEXIT();
  return ret;
}
