#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemsClear(void)
{
  TRACEENTER();

  Menu[CurrentMenuLevel].NrItems = 0;
  ListDirty = TRUE;

  TRACEEXIT();
}
