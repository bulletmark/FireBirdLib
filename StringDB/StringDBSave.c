#include                <string.h>
#include                "../libFireBird.h"

bool StringDBSave(tStringDB *StringDB, char *FileName)
{
  TYPE_File            *f;
  bool                  ret;

  if(!StringDB || !FileName || !StringDB->DB) return FALSE;

  if(TAP_Hdd_Exist(FileName)) TAP_Hdd_Delete(FileName);
  TAP_Hdd_Create(FileName, ATTR_NORMAL);
  f = TAP_Hdd_Fopen(FileName);
  if(!f) return FALSE;

  ret = StringDBSaveToFile(StringDB, f);

  TAP_Hdd_Fclose(f);

  return ret;
}
