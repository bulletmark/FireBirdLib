#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPop(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuPop");
  #endif

  if(CurrentMenuLevel == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  CurrentMenuLevel--;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
