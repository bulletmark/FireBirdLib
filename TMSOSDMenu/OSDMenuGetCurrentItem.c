#include                "FBLib_TMSOSDMenu.h"

int OSDMenuGetCurrentItem(void)
{
  return Menu[CurrentMenuLevel].CurrentSelection;
}
