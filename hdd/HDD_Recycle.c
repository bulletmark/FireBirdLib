#include                <stdio.h>
#include                <string.h>
#include                "libFireBird.h"

bool HDD_Recycle(char *FileName)
{
  TRACEENTER;

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldName[TS_FILE_NAME_SIZE], NewName[TS_FILE_NAME_SIZE], LinuxPath[FBLIB_DIR_SIZE];
  bool                  isRec, isDel, ret;
  int                   fNumber;
  tFileInUse            FileInUse;

  ret = FALSE;
  if(FileName && HDD_Exist(FileName))
  {
    FileInUse = HDD_isFileInUse(FileName);
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

    ConvertPathType(FileName, LinuxPath, PF_FullLinuxPath);
    SeparateFileNameComponents(LinuxPath, Path, Name, Ext, &fNumber, &isRec, &isDel);

    if(!isDel)
    {
      if(fNumber)
        TAP_SPrint(OldName, "%s%s-%d%s", Path, Name, fNumber, Ext);
      else
        TAP_SPrint(OldName, "%s%s%s", Path, Name, Ext);

      TAP_SPrint(NewName, "%s.del", OldName);
      MakeUniqueFileName(NewName);

      if(rename(OldName, NewName) == 0)
      {
        if(isRec && HDD_isRecFileName(FileName))
        {
          //.rec.inf
          strcat(OldName, ".inf");
          NewName[strlen(NewName) - 4] = '\0';
          strcat(NewName, ".inf.del");
          rename(OldName, NewName);

          //.rec.nav
          OldName[strlen(OldName) - 4] = '\0';
          strcat(OldName, ".nav");
          NewName[strlen(NewName) - 8] = '\0';
          strcat(NewName, ".nav.del");
          rename(OldName, NewName);

          //.cut
          OldName[strlen(OldName) - 8] = '\0';
          strcat(OldName, ".cut");
          NewName[strlen(NewName) - 12] = '\0';
          strcat(NewName, ".cut.del");
          rename(OldName, NewName);

          //.cut.bak
          OldName[strlen(OldName) - 4] = '\0';
          strcat(OldName, ".cut.bak");
          NewName[strlen(NewName) - 8] = '\0';
          strcat(NewName, ".cut.bak.del");
          rename(OldName, NewName);

          //.srt
          OldName[strlen(OldName) - 8] = '\0';
          strcat(OldName, ".srt");
          NewName[strlen(NewName) - 12] = '\0';
          strcat(NewName, ".srt.del");
          rename(OldName, NewName);
        }
        ret = TRUE;
      }
    }
  }

  TRACEEXIT;
  return ret;
}
