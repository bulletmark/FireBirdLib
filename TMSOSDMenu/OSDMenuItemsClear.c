#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemsClear(void)
{
  Menu[CurrentMenuLevel].NrItems = 0;
  ListDirty = TRUE;
}
