#include                <string.h>
#include                "../libFireBird.h"

bool StringDBSaveToFile(tStringDB *StringDB, TYPE_File *f)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBSaveToFile");
  #endif

  dword                 l, p;

  if(!StringDB || !f || !StringDB->DB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //DB Size
  l = StringDB->DBEnd - StringDB->DB + 1;
  TAP_Hdd_Fwrite(&l, sizeof(dword), 1, f);

  //Current pointer
  p = StringDB->DBPtr - StringDB->DB;
  TAP_Hdd_Fwrite(&p, sizeof(dword), 1, f);

  TAP_Hdd_Fwrite(StringDB->DB, 1, l, f);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
