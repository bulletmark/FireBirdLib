#include                <string.h>
#include                "../libFireBird.h"

bool StringDBLoad(tStringDB *StringDB, char *FileName)
{
  TYPE_File            *f;
  bool                  ret;

  if(!StringDB || !FileName) return FALSE;

  f = TAP_Hdd_Fopen(FileName);
  if(!f) return FALSE;

  ret = StringDBLoadFromFile(StringDB, f);

  TAP_Hdd_Fclose(f);

  return ret;
}
