#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPush(void)
{
  TRACEENTER();

  if(CurrentMenuLevel >= (NRMENULEVELS - 1))
  {
    TRACEEXIT();
    return FALSE;
  }

  CurrentMenuLevel++;
  memset(&Menu[CurrentMenuLevel], 0, sizeof(tMenu));
  OSDDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
