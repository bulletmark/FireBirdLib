#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetTopIndex(void)
{
  TRACEENTER;

  dword ret;

  ret = Menu[CurrentMenuLevel].CurrentTopIndex;

  TRACEEXIT;
  return ret;
}
