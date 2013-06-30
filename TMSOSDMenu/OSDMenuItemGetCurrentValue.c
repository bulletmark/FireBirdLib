#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentValue(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetCurrentValue");
  #endif

  char *ret;

  ret = OSDMenuItemGetValue(Menu[CurrentMenuLevel].CurrentSelection);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
