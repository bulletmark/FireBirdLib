#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

bool HDD_MoveAbs(char *FileName, char *FromDir, char *ToDir)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_MoveAbs");
  #endif

  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldInfName[512], NewInfName[512];
  bool                  isRec, isDel;
  int                   fNumber;
  char                  OldPath[512], NewPath[512];
  bool                  ret;

  ret = FALSE;
  if(FileName && FromDir && ToDir)
  {
    TAP_SPrint(OldPath, "%s%s%s", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", FileName);
    TAP_SPrint(NewPath, "%s%s%s", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", FileName);
    MakeUniqueFileNameAbs(NewPath);
    rename(OldPath, NewPath);

    SeparateFileNameComponents(OldPath, Name, Ext, &fNumber, &isRec, &isDel);
    if(isRec && strcmp(Ext, ".nav"))
    {
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewPath, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      rename(OldInfName, NewInfName);

      SeparateFileNameComponents(OldPath, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewPath, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      rename(OldInfName, NewInfName);

      ret = TRUE;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
