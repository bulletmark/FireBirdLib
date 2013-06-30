#include                <string.h>
#include                "../libFireBird.h"
#include                "FBLib_hdd.h"

void HDD_RecycleSF(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_RecycleSF");
  #endif

  tFileInUse            FileInUse;
  char                  CurrentPath[512], AbsPath[512];
  tinfBlock             infBlock;

  if(FileName && TAP_Hdd_Exist(FileName))
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

    HDD_TAP_PushDir();
    HDD_ChangeDir("/DataFiles");
    if(!TAP_Hdd_Exist("RecycleBin-")) TAP_Hdd_Create("RecycleBin-", ATTR_FOLDER);
    HDD_TAP_PopDir();

    HDD_TAP_GetCurrentDir(CurrentPath);

    //--------new--------------
    TAP_SPrint(AbsPath, "%s%s/%s", TAPFSROOT, CurrentPath, FileName);

    //Löschzeit in den infBlock eintragen
    HDD_InfBlockGet(AbsPath, &infBlock);
    TAP_SPrint(infBlock.RecoverPath, "%s%s", TAPFSROOT, CurrentPath);
    infBlock.RecycleDate = Now(NULL);
    HDD_InfBlockSet(AbsPath, &infBlock);

    HDD_Move(FileName, CurrentPath, RECYCLEPATH);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
