#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

bool HDD_Rename(char *FileName, char *NewFileName)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldName[TS_FILE_NAME_SIZE], NewName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  bool                  ret;

  ret = FALSE;

  if(FileName && FileName[0] && NewFileName && NewFileName[0] && HDD_Exist(FileName))
  {
    ConvertPathType(FileName, OldName, PF_FullLinuxPath);
    ConvertPathType(NewFileName, NewName, PF_FullLinuxPath);
    MakeUniqueFileName(NewName);

    ret = (rename(OldName, NewName) == 0);

    SeparateFileNameComponents(OldName, Path, Name, Ext, &fNumber, &isRec, &isDel);
    if(isRec)
    {
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d%s.inf%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldName, "%s%s%s.inf%s", Path, Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d%s.inf%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewName, "%s%s%s.inf%s", Path, Name, Ext, isDel ? ".del" : "");

      rename(OldName, NewName);

      SeparateFileNameComponents(OldName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d%s.nav%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldName, "%s%s%s.nav%s", Path, Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d%s.nav%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewName, "%s%s%s.nav%s", Path, Name, Ext, isDel ? ".del" : "");

      rename(OldName, NewName);
    }
  }

  TRACEEXIT();
  return ret;
}
