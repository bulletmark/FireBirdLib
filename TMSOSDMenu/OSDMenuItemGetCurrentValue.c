#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentValue(void)
{
  TRACEENTER();

  char *ret;

  ret = OSDMenuItemGetValue(Menu[CurrentMenuLevel].CurrentSelection);

  TRACEEXIT();
  return ret;
}
