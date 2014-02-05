#include <unistd.h>
#include <string.h>
#include "../libFireBird.h"

dword PlayMediaFileAbs(char *MediaFileName, char *AbsMediaPathName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("PlayMediaFileAbs");
  #endif

  dword                 ret;
  tDirEntry             _TempWorkFolder;
  char                  tempINF[FBLIB_DIR_SIZE];

  ApplHdd_SaveWorkFolder();
  memset(&_TempWorkFolder, 0, sizeof(_TempWorkFolder));
  _TempWorkFolder.Magic = 0xbacaed31;
  ret = ApplHdd_SelectFolder(&_TempWorkFolder, &AbsMediaPathName[1]);
  if(!ret)
  {
    ApplHdd_SetWorkFolder(&_TempWorkFolder);

    sprintf(tempINF, "%s/%s.inf", AbsMediaPathName, MediaFileName);

    if(access(tempINF, F_OK) != -1)
      ret = Appl_StartPlayback(MediaFileName, 0, TRUE, FALSE) == 0;
    else
      ret = Appl_StartPlaybackMedia(MediaFileName, 0, TRUE, FALSE);
  }
  ApplHdd_RestoreWorkFolder();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
