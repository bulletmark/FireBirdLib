#include <string.h>
#include "FBLib_hdd.h"
#include "../libFireBird.h"

bool HDD_ChangeDir(char *Dir)
{
  char                  DirUTF8[256];
  static bool           ReturnTypeToBeChecked = TRUE;
  static int            ChDirSuccessful = 0;

  //The TMS supports absolute paths.
  //Starting with 2009-08-13 (SysID 22010, version 0105), TF changed the return value
  //  of TAP_Hdd_ChangeDir() to the same type as the current TF5000 API
  //The firmware version is not suitable as other machine with this version work well
  if(ReturnTypeToBeChecked)
  {
    ChDirSuccessful = TAP_Hdd_ChangeDir("/ProgramFiles");
    ReturnTypeToBeChecked = FALSE;
  }

  //On some versions, TAP_Hdd_ChangeDir() fails to change into directories with German Umlaute. Try it in UTF-8 format instead.
  if(TAP_Hdd_ChangeDir(Dir) == ChDirSuccessful) return TRUE;

  StrToUTF8(Dir, DirUTF8);
  return (TAP_Hdd_ChangeDir(DirUTF8) == ChDirSuccessful);
}
