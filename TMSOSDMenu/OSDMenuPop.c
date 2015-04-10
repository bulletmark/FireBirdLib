#include                <stdlib.h>
#include                "FBLib_TMSOSDMenu.h"

#undef malloc
#undef free

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
    free(Menu[CurrentMenuLevel].Item);
    Menu[CurrentMenuLevel].Item = NULL;
  }

  CurrentMenuLevel--;

  TRACEEXIT();
  return TRUE;
}
