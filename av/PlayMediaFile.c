#include <string.h>
#include "../libFireBird.h"

dword PlayMediaFile(char *MediaFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("PlayMediaFile");
  #endif

  dword                 ret;
  char                  CurrentDir[FBLIB_DIR_SIZE];

  strcpy(CurrentDir, "/mnt/hd");
  HDD_TAP_GetCurrentDir(&CurrentDir[strlen(CurrentDir)]);
  ret = PlayMediaFileAbs(MediaFileName, CurrentDir);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
