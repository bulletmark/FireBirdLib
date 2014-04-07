#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPop(void)
{
  TRACEENTER();

  if(CurrentMenuLevel == 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  CurrentMenuLevel--;

  TRACEEXIT();
  return TRUE;
}
