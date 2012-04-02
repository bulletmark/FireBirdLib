#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentValue(void)
{
  return OSDMenuItemGetValue(Menu[CurrentMenuLevel].CurrentSelection);
}
