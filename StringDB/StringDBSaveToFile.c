#include                <string.h>
#include                "libFireBird.h"

bool StringDBSaveToFile(tStringDB *StringDB, TYPE_File *f)
{
  TRACEENTER;

  dword                 l, p;

  if(!StringDB || !f || !StringDB->DB)
  {
    TRACEEXIT;
    return FALSE;
  }

  //DB Size
  l = StringDB->DBEnd - StringDB->DB + 1;
  TAP_Hdd_Fwrite(&l, sizeof(dword), 1, f);

  //Current pointer
  p = StringDB->DBPtr - StringDB->DB;
  TAP_Hdd_Fwrite(&p, sizeof(dword), 1, f);

  TAP_Hdd_Fwrite(StringDB->DB, 1, l, f);

  TRACEEXIT;
  return TRUE;
}
