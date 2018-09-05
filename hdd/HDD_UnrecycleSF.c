#include                <stdlib.h>
#include                <string.h>
#include                "libFireBird.h"
#include                "FBLib_hdd.h"

bool HDD_UnrecycleSF(char *FileName)
{
  TRACEENTER;

  tFileInUse            FileInUse;
  char                  AbsPath[FBLIB_DIR_SIZE], AbsFileName[MAX_FILE_NAME_SIZE + 1], *Slash;
  char                  OrigPath[FBLIB_DIR_SIZE];
  char                  CreateOrigPath[FBLIB_DIR_SIZE], cmd[512];
  tinfBlock             infBlock;
  bool                  ret;

  ret = FALSE;
  if(FileName && *FileName && HDD_Exist(FileName))
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

    ConvertPathType(FileName, AbsPath, PF_FullLinuxPath);
    if(*AbsPath)
    {
      //Ursprünglichen Pfad auslesen
      if(HDD_InfBlockGet(AbsPath, &infBlock))
      {
        if(infBlock.RecoverPath[strlen(infBlock.RecoverPath) - 1] != '/') strcat(infBlock.RecoverPath, "/");
        ConvertPathType(infBlock.RecoverPath, OrigPath, PF_LinuxPathOnly);

        //Attribute löschen
        infBlock.RecycleDate = 0;
        infBlock.RecoverPath[0] ='\0';
        HDD_InfBlockSet(AbsPath, &infBlock);

        //Pfad neu anlegen für den Fall das er nicht mehr existiert
        strcpy(CreateOrigPath, OrigPath);
        StrReplace(CreateOrigPath, "\"", "\\\"");
        StrReplace(CreateOrigPath, "$", "\\$");
        TAP_SPrint(cmd, "mkdir -p \"%s\"", CreateOrigPath);
        system(cmd);

        Slash = strrchr(AbsPath, '/');
        strcpy(AbsFileName, Slash + 1);
        Slash[1] = '\0';

        ret = HDD_Move(AbsFileName, AbsPath, OrigPath);
      }
      else
      {
        //No inf available, move to the root directory
        //Use DataFiles as root for the internal disk
        HDD_FindMountPoint(AbsPath, OrigPath);
        if(strcmp("/mnt/hd/", OrigPath) == 0) strcpy(OrigPath, "/mnt/hd/DataFiles/");

        Slash = strrchr(AbsPath, '/');
        strcpy(AbsFileName, Slash + 1);
        Slash[1] = '\0';

        ret = HDD_Move(AbsFileName, AbsPath, OrigPath);
      }
    }
  }

  TRACEEXIT;
  return ret;
}
