#include                <stdlib.h>
#include                "../libFireBird.h"

#undef malloc
#undef free

bool StringDBDestroy(tStringDB *StringDB)
{
  TRACEENTER();

  if(!StringDB)
  {
    TRACEEXIT();
    return FALSE;
  }

  free(StringDB->DB);
  StringDBInit(StringDB, 0);

  TRACEEXIT();
  return TRUE;
}
