#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetCurrentName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetCurrentName");
  #endif

  char *ret;

  ret = OSDMenuItemGetName(Menu[CurrentMenuLevel].CurrentSelection);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
