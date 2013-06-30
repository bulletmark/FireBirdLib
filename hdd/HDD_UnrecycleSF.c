#include                <stdlib.h>
#include                <string.h>
#include                "../libFireBird.h"
#include                "FBLib_hdd.h"

void HDD_UnrecycleSF(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_UnrecycleSF");
  #endif

  char                  OrigPath[512];
  char                  CreateOrigPath[512];
  tinfBlock             infBlock;
  char                  Source1[512], Dest1[512];
  tFileInUse            FileInUse;
  char                  CurrentPath[512], cmd[512];

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

    //Ursprünglichen Pfad auslesen
    HDD_TAP_GetCurrentDir(CurrentPath);
    TAP_SPrint(Source1, "%s%s/%s", TAPFSROOT, CurrentPath, FileName);
    if(HDD_InfBlockGet(Source1, &infBlock))
    {
      strcpy(OrigPath, infBlock.RecoverPath);

      //Attribute löschen
      infBlock.RecycleDate = 0;
      infBlock.RecoverPath[0] ='\0';
      HDD_InfBlockSet(Source1, &infBlock);

      //Pfad neu anlegen für den Fall das er nicht mehr existiert
      strcpy(CreateOrigPath, OrigPath);
      StrReplace(CreateOrigPath, "\"", "\\\"");
      StrReplace(CreateOrigPath, "$", "\\$");
      TAP_SPrint(cmd, "mkdir -p \"/mnt/hd%s\"", CreateOrigPath);
      system(cmd);

      //Verschieben nach OrigPath
      strcpy(Dest1, &infBlock.RecoverPath[7]);
      HDD_Move(FileName, CurrentPath, Dest1);
    }
    else
    {
      //Vermutlich keine INF da, in Root schieben
      HDD_Move(FileName, CurrentPath, "/DataFiles");
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
