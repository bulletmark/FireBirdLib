#include                "../libFireBird.h"

dword StringDBPrev(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBPrev");
  #endif

  char                 *p;
  dword                 ret;

  if(!StringDB || !StringDB->DBPtr || (StringDB->DBPtr <= StringDB->DB))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return '\0';
  }

  p = (StringDB->DBPtr - 2);
  while(*p || (p >= StringDB->DB)) p--;
  p++;
  StringDB->DBPtr = p;
  ret = (dword)p - (dword)StringDB->DB;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
