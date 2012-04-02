#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

bool HDD_Move(char *FileName, char *FromDir, char *ToDir)
{
  char                  cmd[2048];
  char                  NewFileName[TS_FILE_NAME_SIZE];
  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldInfName[TS_FILE_NAME_SIZE], NewInfName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  //char                  cmdUTF8[256];

  HDD_TAP_PushDir();
  if(HDD_ChangeDir(FromDir) == FALSE)
  {
    HDD_TAP_PopDir();
    return FALSE;
  }

  if(TAP_Hdd_Exist(FileName))
  {
    HDD_TAP_PushDir();
    HDD_ChangeDir(ToDir);
    strcpy(NewFileName, FileName);
    MakeUniqueFileName(NewFileName);
    HDD_TAP_PopDir();

    //Build the unix mv command
    TAP_SPrint(cmd, "mv \"%s%s%s%s%s\" ", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", FileName);
    TAP_SPrint(&cmd[strlen(cmd)], "\"%s%s%s%s%s\"", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewFileName);
    //if(TAP_GetVersion() >= 0x0108)
    //{
    //  StrToUTF8(cmd, cmdUTF8);
    //  strcpy(cmd, cmdUTF8);
    //}
    system(cmd);

    SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);
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

      //Build the unix mv command
      TAP_SPrint(cmd, "mv \"%s%s%s%s%s\" ", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", OldInfName);
      TAP_SPrint(&cmd[strlen(cmd)], "\"%s%s%s%s%s\"", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewInfName);
      //if(TAP_GetVersion() >= 0x0108)
      //{
      //  StrToUTF8(cmd, cmdUTF8);
      //  strcpy(cmd, cmdUTF8);
      //}
      system(cmd);

      SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      //Build the unix mv command
      TAP_SPrint(cmd, "mv \"%s%s%s%s%s\" ", TAPFSROOT, (FromDir[0] != '/') ? "/" : "", FromDir, (FromDir[strlen(FromDir) - 1] != '/') ? "/" : "", OldInfName);
      TAP_SPrint(&cmd[strlen(cmd)], "\"%s%s%s%s%s\"", TAPFSROOT, (ToDir[0] != '/') ? "/" : "", ToDir, (ToDir[strlen(ToDir) - 1] != '/') ? "/" : "", NewInfName);
      //if(TAP_GetVersion() >= 0x0108)
      //{
      //  StrToUTF8(cmd, cmdUTF8);
      //  strcpy(cmd, cmdUTF8);
      //}
      system(cmd);
    }
  }
  else
  {
    HDD_TAP_PopDir();
    return FALSE;
  }
  HDD_TAP_PopDir();

  return TRUE;
}
