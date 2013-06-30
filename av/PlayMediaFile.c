#include <string.h>
#include "../libFireBird.h"

dword PlayMediaFile(char *MediaFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("PlayMediaFile");
  #endif

  dword                 ret;
  tDirEntry             _TempWorkFolder;
  char                  CurrentDir[FBLIB_DIR_SIZE];
  static dword         *_hddDivxFolder = NULL;

  if(!_hddDivxFolder) _hddDivxFolder = (dword*)FIS_vHddDivxFolder();
  if(!_hddDivxFolder)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 7;
  }

  ApplHdd_SaveWorkFolder();
  strcpy(CurrentDir, "mnt/hd");
  HDD_TAP_GetCurrentDir(&CurrentDir[strlen(CurrentDir)]);
  memset(&_TempWorkFolder, 0, sizeof(_TempWorkFolder));
  _TempWorkFolder.Magic = 0xbacaed31;
  ret = ApplHdd_SelectFolder(&_TempWorkFolder, CurrentDir);

  if(!ret)
  {
    ApplHdd_SetWorkFolder(&_TempWorkFolder);
    memcpy((void*)_hddDivxFolder[0], &_TempWorkFolder, sizeof(_TempWorkFolder));
    ret = Appl_StartPlaybackMedia(MediaFileName, 0, TRUE, FALSE);
  }
  ApplHdd_RestoreWorkFolder();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
