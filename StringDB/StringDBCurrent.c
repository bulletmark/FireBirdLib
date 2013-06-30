#include                "../libFireBird.h"

dword StringDBCurrent(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBCurrent");
  #endif

  dword ret;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return '\0';
  }
  ret = (dword)StringDB->DBPtr - (dword)StringDB->DB;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
