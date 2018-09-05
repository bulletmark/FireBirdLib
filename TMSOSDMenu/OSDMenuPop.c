#include                <stdlib.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPop(void)
{
  TRACEENTER;

  if(CurrentMenuLevel == 0)
  {
    TRACEEXIT;
    return FALSE;
  }

  if(Menu[CurrentMenuLevel].Item)
  {
    TAP_MemFree(Menu[CurrentMenuLevel].Item);
    Menu[CurrentMenuLevel].Item = NULL;
  }

  CurrentMenuLevel--;

  TRACEEXIT;
  return TRUE;
}
