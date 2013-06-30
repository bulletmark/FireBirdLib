#include                "FBLib_TMSOSDMenu.h"

int OSDMenuGetCurrentItem(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuGetCurrentItem");
  #endif

  int ret = Menu[CurrentMenuLevel].CurrentSelection;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
