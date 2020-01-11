#include                <stdlib.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPop(void)
{
  TRACEENTER();

  if(CurrentMenuLevel == 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(Menu[CurrentMenuLevel].Item)
  {
    TAP_MemFree(Menu[CurrentMenuLevel].Item);
    Menu[CurrentMenuLevel].Item = NULL;
  }

  if (Menu[CurrentMenuLevel].MemoText)
  {
    TAP_MemFree(Menu[CurrentMenuLevel].MemoText);
    Menu[CurrentMenuLevel].MemoText = NULL;
  }

  CurrentMenuLevel--;
  OSDDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
