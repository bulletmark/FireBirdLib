#include "FBLib_tap.h"

bool HDD_TAP_PopDir(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_PopDir");
  #endif

  if(TAPDirStackDepth >= 0)
  {
    bool ret = HDD_ChangeDir(TAPDirStack[TAPDirStackDepth--]);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return ret;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
