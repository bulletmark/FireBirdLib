#include "FBLib_tap.h"

char                    TAPDirStack[TAPDIR_MAX_STACK][200];
int                     TAPDirStackDepth = -1;

bool HDD_TAP_PushDir (void)
{
  if (++TAPDirStackDepth < TAPDIR_MAX_STACK)
  {
    if (HDD_TAP_GetCurrentDir(TAPDirStack[TAPDirStackDepth]) == 0) return TRUE;
  }
  TAPDirStackDepth--;
  return FALSE;
}
