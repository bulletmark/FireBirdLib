#include                "../libFireBird.h"

dword StringDBFirst(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBFirst");
  #endif

  dword ret;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return '\0';
  }

  StringDB->DBPtr = StringDB->DB;
  ret = (dword)StringDB->DBPtr - (dword)StringDB->DB;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
