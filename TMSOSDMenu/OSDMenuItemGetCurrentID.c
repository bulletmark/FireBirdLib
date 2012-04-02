#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetCurrentID(void)
{
  return OSDMenuItemGetID(Menu[CurrentMenuLevel].CurrentSelection);
}
