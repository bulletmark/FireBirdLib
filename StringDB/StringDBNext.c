#include                "../libFireBird.h"

dword StringDBNext(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBNext");
  #endif

  char                 *p;
  dword                 ret;

  if(!StringDB || !StringDB->DBPtr || (StringDB->DBPtr >= StringDB->DBEnd))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return '\0';
  }

  p = StringDB->DBPtr;
  while(*p) p++;
  p++;
  StringDB->DBPtr = p;
  ret = (dword)p - (dword)StringDB->DB;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
