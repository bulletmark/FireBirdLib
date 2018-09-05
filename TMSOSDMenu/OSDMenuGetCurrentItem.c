#include                "FBLib_TMSOSDMenu.h"

int OSDMenuGetCurrentItem(void)
{
  TRACEENTER;

  int ret = Menu[CurrentMenuLevel].CurrentSelection;

  TRACEEXIT;
  return ret;
}
