#include                <stdlib.h>
#include                <string.h>
#include                "../libFireBird.h"

bool StringDBLoadFromFile(tStringDB *StringDB, TYPE_File *f)
{
  TRACEENTER();

  dword                 l, p;

  if(!StringDB || !f)
  {
    TRACEEXIT();
    return FALSE;
  }

  TAP_MemFree(StringDB->DB);

  //DB Size
  TAP_Hdd_Fread(&l, sizeof(dword), 1, f);
  StringDB->DB = TAP_MemAlloc(l);

  if(!StringDB->DB)
  {
    StringDB->DBSize = 0;
    TAP_Hdd_Fclose(f);

    TRACEEXIT();
    return FALSE;
  }
  StringDB->DBSize = l;
  StringDB->DBEnd = l + StringDB->DB - 1;

  //Current pointer
  TAP_Hdd_Fread(&p, sizeof(dword), 1, f);
  StringDB->DBPtr = p + StringDB->DB;

  TAP_Hdd_Fread(StringDB->DB, 1, l, f);

  TRACEEXIT();
  return TRUE;
}
