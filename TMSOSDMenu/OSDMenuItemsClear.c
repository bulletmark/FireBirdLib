#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemsClear(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemsClear");
  #endif

  Menu[CurrentMenuLevel].NrItems = 0;
  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
