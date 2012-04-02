#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPop(void)
{
  if(CurrentMenuLevel == 0) return FALSE;

  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  CurrentMenuLevel--;

  return TRUE;
}
