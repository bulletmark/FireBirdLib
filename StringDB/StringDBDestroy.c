#include                <stdlib.h>
#include                "../libFireBird.h"

bool StringDBDestroy(tStringDB *StringDB)
{
  TRACEENTER();

  if(!StringDB)
  {
    TRACEEXIT();
    return FALSE;
  }

  TAP_MemFree(StringDB->DB);
  StringDBInit(StringDB, 0);

  TRACEEXIT();
  return TRUE;
}
