#include                <string.h>
#include                "../libFireBird.h"

tFileInUse HDD_isFileInUse(char *FileName)
{
  TRACEENTER();

  TYPE_PlayInfo         PlayInfo;
  int                   i, NrRecSlots;
  char                  WorkingFileName[FBLIB_DIR_SIZE];
  char                  AbsFileName[FBLIB_DIR_SIZE];
  TYPE_File            *RecFile;

  if(!FileName || !*FileName)
  {
    TRACEEXIT();
    return FIU_No;
  }

  //Convert to an Linux path and cut away any .inf or .nav
  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
  if(StringEndsWith(AbsFileName, ".inf")) AbsFileName[strlen(AbsFileName) - 4] = '\0';

  //Is any Playback running
  TAP_Hdd_GetPlayInfo(&PlayInfo);
  if(PlayInfo.playMode && PlayInfo.totalBlock > 0)
  {
    //Compare the full path of both files
    HDD_GetAbsolutePathByTypeFile(PlayInfo.file, WorkingFileName);
    if(StringEndsWith(WorkingFileName, ".inf") || StringEndsWith(WorkingFileName, ".nav")) WorkingFileName[strlen(WorkingFileName) - 4] = '\0';

    if(!strcmp(AbsFileName, WorkingFileName))
    {
      if(PlayInfo.playMode == PLAYMODE_Mp3)
      {
        TRACEEXIT();
        return FIU_PlayMP3;
      }
      else
      {
        TRACEEXIT();
        return FIU_Playback;
      }
    }
  }

  //Loop through all recording slots
  NrRecSlots = (int)HDD_NumberOfRECSlots();
  for(i = 0; i < NrRecSlots; i++)
  {
    //Get the full path of the rec file
    if(HDD_GetRecSlotFiles(i, &RecFile, NULL, NULL) && HDD_GetAbsolutePathByTypeFile(RecFile, WorkingFileName))
    {
      //Check if both paths are equal
      if(!strcmp(AbsFileName, WorkingFileName))
      {
        TRACEEXIT();
        return (FIU_RecSlot1 + i);
      }
    }
  }

  TRACEEXIT();
  return FIU_No;
}
