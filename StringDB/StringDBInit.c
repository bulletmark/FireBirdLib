#include                "../libFireBird.h"

bool StringDBInit(tStringDB *StringDB, dword InitialSize)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBInit");
  #endif

  bool ret;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  StringDB->DBSize = InitialSize;
  if(InitialSize)
  {
    StringDB->DB = TAP_MemAlloc(InitialSize);
    if(StringDB->DB) TAP_MemSet(StringDB->DB, 0, InitialSize);
  }
  else
    StringDB->DB = NULL;

  StringDB->DBPtr = StringDB->DB;
  StringDB->DBEnd = StringDB->DB;
  ret  =(StringDB->DB != NULL) || (InitialSize == 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
