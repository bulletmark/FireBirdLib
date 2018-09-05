#include "FBLib_tap.h"

bool HDD_TAP_PopDir(void)
{
  TRACEENTER;

  if(TAPDirStackDepth >= 0)
  {
    bool ret = HDD_ChangeDir(TAPDirStack[TAPDirStackDepth--]);

    TRACEEXIT;
    return ret;
  }

  TRACEEXIT;
  return FALSE;
}
