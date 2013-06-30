#include                <string.h>
#include                "../libFireBird.h"

bool StringDBLoad(tStringDB *StringDB, char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBLoad");
  #endif

  TYPE_File            *f;
  bool                  ret;

  if(!StringDB || !FileName)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  f = TAP_Hdd_Fopen(FileName);
  if(!f)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  ret = StringDBLoadFromFile(StringDB, f);

  TAP_Hdd_Fclose(f);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
