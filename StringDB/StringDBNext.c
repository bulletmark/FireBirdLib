#include                "../libFireBird.h"

dword StringDBNext(tStringDB *StringDB)
{
  char                 *p;

  if(!StringDB || !StringDB->DBPtr || (StringDB->DBPtr >= StringDB->DBEnd)) return '\0';

  p = StringDB->DBPtr;
  while(*p) p++;
  p++;
  StringDB->DBPtr = p;

  return (dword)p - (dword)StringDB->DB;
}
