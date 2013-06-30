#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetCurrentID(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetCurrentID");
  #endif

  dword ret;

  ret = OSDMenuItemGetID(Menu[CurrentMenuLevel].CurrentSelection);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
