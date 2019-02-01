#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemsClear(void)
{
  TRACEENTER();

  Menu[CurrentMenuLevel].NrItems = 0;
  Menu[CurrentMenuLevel].CurrentSelection = 0;
  Menu[CurrentMenuLevel].CurrentTopIndex = 0;
  ListDirty = TRUE;

  TRACEEXIT();
}
