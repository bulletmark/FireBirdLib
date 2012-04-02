#include                "../libFireBird.h"

bool StringDBDestroy(tStringDB *StringDB)
{
  if(!StringDB) return FALSE;

  if(StringDB->DB) TAP_MemFree(StringDB->DB);
  StringDBInit(StringDB, 0);

  return TRUE;
}
