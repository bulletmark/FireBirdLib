#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_hdd.h"
#include                "libFireBird.h"

bool HDD_Move(const char *FileName, const char *FromDir, const char *ToDir)
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
        //.rec.inf
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

        //.rec.nav
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

        //.cut
        SeparateFileNameComponents(OldPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(OldInfName, "%s%s-%d.cut%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(OldInfName, "%s%s.cut%s", Path, Name, isDel ? ".del" : "");

        SeparateFileNameComponents(NewPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(NewInfName, "%s%s-%d.cut%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(NewInfName, "%s%s.cut%s", Path, Name, isDel ? ".del" : "");

        rename(OldInfName, NewInfName);

        //.cut.bak
        SeparateFileNameComponents(OldPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(OldInfName, "%s%s-%d.cut.bak%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(OldInfName, "%s%s.cut.bak%s", Path, Name, isDel ? ".del" : "");

        SeparateFileNameComponents(NewPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(NewInfName, "%s%s-%d.cut.bak%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(NewInfName, "%s%s.cut.bak%s", Path, Name, isDel ? ".del" : "");

        rename(OldInfName, NewInfName);

        //.srt
        SeparateFileNameComponents(OldPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(OldInfName, "%s%s-%d.srt%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(OldInfName, "%s%s.srt%s", Path, Name, isDel ? ".del" : "");

        SeparateFileNameComponents(NewPath, Path, Name, Ext, &fNumber, &isRec, &isDel);
        if(fNumber)
          TAP_SPrint(NewInfName, "%s%s-%d.srt%s", Path, Name, fNumber, isDel ? ".del" : "");
        else
          TAP_SPrint(NewInfName, "%s%s.srt%s", Path, Name, isDel ? ".del" : "");

        rename(OldInfName, NewInfName);

        ret = TRUE;
      }
    }
  }

  TRACEEXIT();
  return ret;
}
