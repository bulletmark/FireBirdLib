#include                <stdio.h>
#include                <string.h>
#include                "libFireBird.h"

void HDD_Delete(char *FileName)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  TempName[FBLIB_DIR_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  char                  AbsFileName[FBLIB_DIR_SIZE];
  tFileInUse            FileInUse;

  if(!FileName || !*FileName)
  {
    TRACEEXIT();
    return;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);

  if(*AbsFileName)
  {
    FileInUse = HDD_isFileInUse(AbsFileName);
    switch(FileInUse)
    {
      case FIU_No: break;

       //Do not differentiate because of a firmware bug
      case FIU_Playback:
      case FIU_PlayMP3:
      {
        TAP_Hdd_StopTs();
        TAP_Hdd_StopMp3();
        break;
      }

      case FIU_RecSlot1: TAP_Hdd_StopRecord(0); break;
      case FIU_RecSlot2: TAP_Hdd_StopRecord(1); break;
      case FIU_RecSlot3: TAP_Hdd_StopRecord(2); break;
      case FIU_RecSlot4: TAP_Hdd_StopRecord(3); break;
    }

    if(StringEndsWith(AbsFileName, ".rec.inf")) AbsFileName[strlen(AbsFileName) - 4] = '\0';
    if(StringEndsWith(AbsFileName, ".rec.nav")) AbsFileName[strlen(AbsFileName) - 4] = '\0';

    if(StringEndsWith(AbsFileName, ".mpg.inf")) AbsFileName[strlen(AbsFileName) - 4] = '\0';
    if(StringEndsWith(AbsFileName, ".mpg.nav")) AbsFileName[strlen(AbsFileName) - 4] = '\0';

    if(StringEndsWith(AbsFileName, ".ts.inf")) AbsFileName[strlen(AbsFileName) - 4] = '\0';
    if(StringEndsWith(AbsFileName, ".ts.nav")) AbsFileName[strlen(AbsFileName) - 4] = '\0';

    remove(AbsFileName);

    SeparateFileNameComponents(AbsFileName, Path, Name, Ext, &fNumber, &isRec, &isDel);

    if(isRec)
    {
      //.rec.inf
      if(fNumber)
        TAP_SPrint(TempName, "%s%s-%d%s.inf%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(TempName, "%s%s%s.inf%s", Path, Name, Ext, isDel ? ".del" : "");
      remove(TempName);

      //.rec.nav
      if(fNumber)
        TAP_SPrint(TempName, "%s%s-%d%s.nav%s", Path, Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(TempName, "%s%s%s.nav%s", Path, Name, Ext, isDel ? ".del" : "");
      remove(TempName);

      //.cut
      if(fNumber)
        TAP_SPrint(TempName, "%s%s-%d.cut%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(TempName, "%s%s.cut%s", Path, Name, isDel ? ".del" : "");
      remove(TempName);

      //.cut.bak
      if(fNumber)
        TAP_SPrint(TempName, "%s%s-%d.cut.bak%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(TempName, "%s%s.cut.bak%s", Path, Name, isDel ? ".del" : "");
      remove(TempName);

      //.srt
      if(fNumber)
        TAP_SPrint(TempName, "%s%s-%d.srt%s", Path, Name, fNumber, isDel ? ".del" : "");
      else
        TAP_SPrint(TempName, "%s%s.srt%s", Path, Name, isDel ? ".del" : "");
      remove(TempName);
    }
  }

  TRACEEXIT();
}
