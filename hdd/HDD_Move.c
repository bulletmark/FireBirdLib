#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

bool HDD_Move(char *FileName, char *FromDir, char *ToDir)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldInfName[FBLIB_DIR_SIZE], NewInfName[FBLIB_DIR_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  char                  OldPath[FBLIB_DIR_SIZE], NewPath[FBLIB_DIR_SIZE];
  bool                  ret;

  ret = FALSE;
  if(FileName && *FileName && FromDir && ToDir)
  {
    ConvertPathType(FromDir, OldPath, PF_LinuxPathOnly);
    strcat(OldPath, FileName);
    if(HDD_Exist(OldPath))
    {
      ConvertPathType(ToDir, NewPath, PF_LinuxPathOnly);
      strcat(NewPath, FileName);

      MakeUniqueFileName(NewPath);
      if(rename(OldPath, NewPath) != 0)
      {
        TRACEEXIT();
        return FALSE;
      }

      SeparateFileNameComponents(OldPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(isRec && strcmp(Ext, ".nav"))
      {
        if(fNumber)
          TAP_SPrint(OldInfName, "%s%s-%d%s.inf%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
        else
          TAP_SPrint(OldInfName, "%s%s%s.inf%s", Path, Name, Ext, isDel ? ".del" : "");

        SeparateFileNameComponents(NewPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(NewInfName, "%s%s-%d%s.inf%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
        else
          TAP_SPrint(NewInfName, "%s%s%s.inf%s", Path, Name, Ext, isDel ? ".del" : "");

        rename(OldInfName, NewInfName);

        SeparateFileNameComponents(OldPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(OldInfName, "%s%s-%d%s.nav%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
        else
          TAP_SPrint(OldInfName, "%s%s%s.nav%s", Path, Name, Ext, isDel ? ".del" : "");

        SeparateFileNameComponents(NewPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(NewInfName, "%s%s-%d%s.nav%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
        else
          TAP_SPrint(NewInfName, "%s%s%s.nav%s", Path, Name, Ext, isDel ? ".del" : "");

        rename(OldInfName, NewInfName);

        ret = TRUE;
      }
    }
  }

  TRACEEXIT();
  return ret;
}
