#include                <sys/stat.h>
#include                <string.h>
#include                "libFireBird.h"
#include                "FBLib_hdd.h"

bool HDD_RecycleSF(const char *FileName)
{
  TRACEENTER();

  tFileInUse            FileInUse;
  char                  AbsPath[FBLIB_DIR_SIZE], AbsFileName[MAX_FILE_NAME_SIZE + 1], *Slash;
  char                  RecycleDir[FBLIB_DIR_SIZE], MountPoint[FBLIB_DIR_SIZE];
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
      char c;

      Slash = strrchr(AbsPath, '/');
      c = *Slash;
      *Slash = '\0';

      //Set the deletion time in the infBlock
      HDD_InfBlockGet(FileName, &infBlock);
      strcpy(infBlock.RecoverPath, AbsPath);
      infBlock.RecycleDate = Now(NULL);
      HDD_InfBlockSet(FileName, &infBlock);

      //Separate
      *Slash = c;
      strcpy(AbsFileName, Slash + 1);
      Slash[1] = '\0';

      //Find the mount point for that drive and create a RecycleBin folder in the root.
      //Use DataFiles as root for the internal disk
      HDD_FindMountPoint(AbsPath, MountPoint);
      if(strcmp("/mnt/hd/", MountPoint) == 0) strcpy(MountPoint, "/mnt/hd/DataFiles/");

      TAP_SPrint(RecycleDir, "%sRecycleBin-", MountPoint);
      mkdir(RecycleDir, 0777);
      ret = HDD_Move(AbsFileName, AbsPath, RecycleDir);
    }
  }

  TRACEEXIT();
  return ret;
}
