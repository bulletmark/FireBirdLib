#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPush(void)
{
  if(CurrentMenuLevel >= (NRMENULEVELS - 1)) return FALSE;

  CurrentMenuLevel++;
  memset(&Menu[CurrentMenuLevel], 0, sizeof(tMenu));

  return TRUE;
}
