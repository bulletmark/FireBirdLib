#include                "../libFireBird.h"

bool StringDBEOF(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBEOF");
  #endif

  bool ret;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }
  ret = (StringDB->DBPtr[0] == '\0');

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
