#include "FBLib_tap.h"

char                    TAPDirStack[TAPDIR_MAX_STACK][200];
int                     TAPDirStackDepth = -1;

bool HDD_TAP_PushDir(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_PushDir");
  #endif

  if(++TAPDirStackDepth < TAPDIR_MAX_STACK)
  {
    if(HDD_TAP_GetCurrentDir(TAPDirStack[TAPDirStackDepth]) == 0)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }
  }
  TAPDirStackDepth--;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
