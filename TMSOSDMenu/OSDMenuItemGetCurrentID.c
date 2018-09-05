#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetCurrentID(void)
{
  TRACEENTER;

  dword ret;

  ret = OSDMenuItemGetID(Menu[CurrentMenuLevel].CurrentSelection);

  TRACEEXIT;
  return ret;
}
