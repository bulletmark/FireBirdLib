#include                <string.h>
#include                "../libFireBird.h"

bool StringDBSaveToFile(tStringDB *StringDB, TYPE_File *f)
{
  dword                 l, p;

  if(!StringDB || !f || !StringDB->DB) return FALSE;

  //DB Size
  l = StringDB->DBEnd - StringDB->DB + 1;
  TAP_Hdd_Fwrite(&l, sizeof(dword), 1, f);

  //Current pointer
  p = StringDB->DBPtr - StringDB->DB;
  TAP_Hdd_Fwrite(&p, sizeof(dword), 1, f);

  TAP_Hdd_Fwrite(StringDB->DB, 1, l, f);

  return TRUE;
}
