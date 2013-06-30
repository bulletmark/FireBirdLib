#include <string.h>
#include "FBLib_hdd.h"
#include "../libFireBird.h"

bool HDD_ChangeDir(char *Dir)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_ChangeDir");
  #endif

  char                  DirUTF8[256];
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

  if(Dir)
  {
    if(TAP_Hdd_ChangeDir(Dir) == ChDirSuccessful)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }

    //On some versions, TAP_Hdd_ChangeDir() fails to change into directories with German Umlaute. Try it in UTF-8 format instead.
    if(isUTFToppy())
    {
      StrToUTF8(Dir, DirUTF8, 9);
      if(TAP_Hdd_ChangeDir(DirUTF8) == ChDirSuccessful)
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return TRUE;
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
