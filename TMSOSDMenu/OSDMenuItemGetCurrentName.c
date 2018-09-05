#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentName(void)
{
  TRACEENTER;

  char *ret;

  ret = OSDMenuItemGetName(Menu[CurrentMenuLevel].CurrentSelection);

  TRACEEXIT;
  return ret;
}
