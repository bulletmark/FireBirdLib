#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentName(void)
{
  return OSDMenuItemGetName(Menu[CurrentMenuLevel].CurrentSelection);
}
