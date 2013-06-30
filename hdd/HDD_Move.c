#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

bool HDD_Move(char *FileName, char *FromDir, char *ToDir)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_Move");
  #endif

  char                  OldFileName[TS_FILE_NAME_SIZE], NewFileName[TS_FILE_NAME_SIZE];
  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldInfName[TS_FILE_NAME_SIZE], NewInfName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  char                  OldPath[512], NewPath[512];

  HDD_TAP_PushDir();
  if(HDD_ChangeDir(FromDir) == FALSE)
  {
    HDD_TAP_PopDir();

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(FileName && FromDir && ToDir && TAP_Hdd_Exist(FileName))
  {
    HDD_TAP_PushDir();
    HDD_ChangeDir(ToDir);
    strcpy(OldFileName, FileName);
    StrReplace(OldFileName, "\"", "\\\"");
    StrReplace(OldFileName, "$", "\\$");

    strcpy(NewFileName, FileName);
    MakeUniqueFileName(NewFileName);
    StrReplace(NewFileName, "\"", "\\\"");
    StrReplace(NewFileName, "$", "\\$");
    HDD_TAP_PopDir();

    TAP_SPrint(OldPath, "%s%s%s%s%s", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", OldFileName);
    TAP_SPrint(NewPath, "%s%s%s%s%s", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewFileName);
    rename(OldPath, NewPath);

    SeparateFileNameComponents(OldFileName, Name, Ext, &fNumber, &isRec, &isDel);
    if(isRec && strcmp(Ext, ".nav"))
    {
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      TAP_SPrint(OldPath, "%s%s%s%s%s", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", OldInfName);
      TAP_SPrint(NewPath, "%s%s%s%s%s", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewInfName);
      rename(OldPath, NewPath);

      SeparateFileNameComponents(OldFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      TAP_SPrint(OldPath, "%s%s%s%s%s", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", OldInfName);
      TAP_SPrint(NewPath, "%s%s%s%s%s", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewInfName);
      rename(OldPath, NewPath);
    }
  }
  else
  {
    HDD_TAP_PopDir();

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }
  HDD_TAP_PopDir();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
