#include                <stdio.h>
#include                <string.h>
#include                "libFireBird.h"

bool HDD_Rename(char *FileName, char *NewFileName)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[512], Ext[512];
  char                  OldName[512], NewName[512];
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
      //.rec.inf
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

      //.rec.nav
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

      //.cut
      SeparateFileNameComponents(OldName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d.cut%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(OldName, "%s%s.cut%s", Path, Name, isDel ? ".del" : "");

      SeparateFileNameComponents(NewName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d.cut%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(NewName, "%s%s.cut%s", Path, Name, isDel ? ".del" : "");

      rename(OldName, NewName);

      //.cut.bak
      SeparateFileNameComponents(OldName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d.cut.bak%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(OldName, "%s%s.cut.bak%s", Path, Name, isDel ? ".del" : "");

      SeparateFileNameComponents(NewName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d.cut.bak%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(NewName, "%s%s.cut.bak%s", Path, Name, isDel ? ".del" : "");

      rename(OldName, NewName);

      //.srt
      SeparateFileNameComponents(OldName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      Name[strlen(Name) - 4] = '\0';    //Remove .cut from name
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d.srt%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(OldName, "%s%s.srt%s", Path, Name, isDel ? ".del" : "");

      SeparateFileNameComponents(NewName, Path, Name, Ext, &fNumber, &isRec, &isDel);
      Name[strlen(Name) - 4] = '\0';    //Remove .cut from name
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d.srt%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(NewName, "%s%s.srt%s", Path, Name, isDel ? ".del" : "");

      rename(OldName, NewName);
    }
  }

  TRACEEXIT();
  return ret;
}
