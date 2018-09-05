#include "FBLib_tap.h"

char                    TAPDirStack[TAPDIR_MAX_STACK][200];
int                     TAPDirStackDepth = -1;

bool HDD_TAP_PushDir(void)
{
  TRACEENTER;

  if(++TAPDirStackDepth < TAPDIR_MAX_STACK)
  {
    if(HDD_TAP_GetCurrentDir(TAPDirStack[TAPDirStackDepth]) == 0)
    {
      TRACEEXIT;
      return TRUE;
    }
  }
  TAPDirStackDepth--;

  TRACEEXIT;
  return FALSE;
}
