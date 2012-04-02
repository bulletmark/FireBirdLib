#include                "../libFireBird.h"

bool StringDBInit(tStringDB *StringDB, dword InitialSize)
{
  if(!StringDB) return FALSE;

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

  return (StringDB->DB != NULL) || (InitialSize == 0);
}
