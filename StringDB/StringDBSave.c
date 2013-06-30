#include                <string.h>
#include                "../libFireBird.h"

bool StringDBSave(tStringDB *StringDB, char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBSave");
  #endif

  TYPE_File            *f;
  bool                  ret;

  if(!StringDB || !FileName || !StringDB->DB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(TAP_Hdd_Exist(FileName)) TAP_Hdd_Delete(FileName);
  TAP_Hdd_Create(FileName, ATTR_NORMAL);
  f = TAP_Hdd_Fopen(FileName);
  if(!f)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  ret = StringDBSaveToFile(StringDB, f);

  TAP_Hdd_Fclose(f);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
