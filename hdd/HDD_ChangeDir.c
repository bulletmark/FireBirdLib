#include <string.h>
#include "FBLib_hdd.h"
#include "libFireBird.h"

bool HDD_ChangeDir(const char *Dir)
{
  TRACEENTER();

  char                  s[FBLIB_DIR_SIZE], TAPDir[FBLIB_DIR_SIZE], DirUTF8[FBLIB_DIR_SIZE];
  static bool           ReturnTypeToBeChecked = TRUE;
  static int            ChDirSuccessful = 0;

  //The TMS supports absolute paths.

  //Starting with 2009-08-13 (SysID 22010, version 0105), TF changed the return value
  //  of TAP_Hdd_ChangeDir() to the same type as the current TF5000 API
  //Get a good return value by changing to a well known directory
  if(ReturnTypeToBeChecked)
  {
    HDD_TAP_PushDir();
    ChDirSuccessful = TAP_Hdd_ChangeDir("/ProgramFiles");
    ReturnTypeToBeChecked = FALSE;
    HDD_TAP_PopDir();
  }

  if(Dir && *Dir)
  {
    strcpy(s, Dir);
    if(s[strlen(s) - 1] != '/') strcat(s, "/");
    ConvertPathType(s, TAPDir, PF_TAPPathOnly);
    if(!*TAPDir)
    {
      TRACEEXIT();
      return FALSE;
    }

    if(TAP_Hdd_ChangeDir(TAPDir) == ChDirSuccessful)
    {
      TRACEEXIT();
      return TRUE;
    }

    //On some versions, TAP_Hdd_ChangeDir() fails to change into directories with German Umlaute. Try it in UTF-8 format instead.
    if(isUTFToppy())
    {
      StrToUTF8(TAPDir, DirUTF8, 9);
      if(TAP_Hdd_ChangeDir(DirUTF8) == ChDirSuccessful)
      {
        TRACEEXIT();
        return TRUE;
      }
    }
  }

  TRACEEXIT();
  return FALSE;
}
