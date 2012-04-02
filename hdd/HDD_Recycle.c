#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

void HDD_Recycle(char *FileName)
{
  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldName[TS_FILE_NAME_SIZE], NewName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  tFileInUse            FileInUse;

  if (TAP_Hdd_Exist(FileName))
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

    SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);

    if(!isDel)
    {
      if(fNumber)
        TAP_SPrint(OldName, "%s-%d%s", Name, fNumber, Ext);
      else
        TAP_SPrint(OldName, "%s%s", Name, Ext);

      TAP_SPrint(NewName, "%s.del", OldName);
      MakeUniqueFileName(NewName);
      TAP_Hdd_Rename(OldName, NewName);

      if(isRec && (StringEndsWith(FileName, ".rec") || StringEndsWith(FileName, ".mpg")))
      {
        strcat(OldName, ".inf");
        NewName[strlen(NewName) - 4] = '\0';
        strcat(NewName, ".inf.del");
        TAP_Hdd_Rename(OldName, NewName);

        OldName[strlen(OldName) - 4] = '\0';
        strcat(OldName, ".nav");
        NewName[strlen(NewName) - 8] = '\0';
        strcat(NewName, ".nav.del");
        TAP_Hdd_Rename(OldName, NewName);
      }
    }
  }
}
