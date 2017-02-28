#include <unistd.h>
#include <string.h>
#include "../libFireBird.h"

bool PlayMediaFile(char *MediaFileName)
{
  TRACEENTER();

  bool                  ret;
  tDirEntry             _TempWorkFolder;
  char                  tempINF[FBLIB_DIR_SIZE];
  char                  TempFileName[FBLIB_DIR_SIZE];

  ApplHdd_SaveWorkFolder();
  memset(&_TempWorkFolder, 0, sizeof(_TempWorkFolder));
  _TempWorkFolder.Magic = 0xbacaed31;

  ConvertPathType(MediaFileName, TempFileName, PF_LinuxPathOnly);
  if(StringEndsWith(TempFileName, "/")) TempFileName[strlen(TempFileName) - 1] = '\0';
  ret = ApplHdd_SelectFolder(&_TempWorkFolder, &TempFileName[1]);

  if(!ret)
  {
    ApplHdd_SetWorkFolder(&_TempWorkFolder);

    ConvertPathType(MediaFileName, tempINF, PF_FullLinuxPath);
    strcat(tempINF, ".inf");
    ConvertPathType(MediaFileName, TempFileName, PF_FileNameOnly);

    if((access(tempINF, F_OK) != -1) && HDD_isRecFileName(MediaFileName) && !StringEndsWith(TempFileName, ".ts"))
      ret = Appl_StartPlayback(TempFileName, 0, TRUE, FALSE) == 0;
    else if(StringEndsWith(TempFileName, ".avi") || StringEndsWith(TempFileName, ".divx"))
    {
      ret = Appl_StartPlaybackDivx(TempFileName, 0, FALSE) == 0;
    }
    else if(StringEndsWith(TempFileName, ".mp3"))
    {
      ret = Appl_StartPlaybackMp3(TempFileName) == 0;
    }
    else
    {
      ret = Appl_StartPlaybackMedia(TempFileName, 0, TRUE, FALSE) == 0;
    }
  }
  ApplHdd_RestoreWorkFolder();

  TRACEEXIT();
  return ret;
}
