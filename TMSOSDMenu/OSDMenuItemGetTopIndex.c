#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetTopIndex(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetTopIndex");
  #endif

  dword ret;

  ret = Menu[CurrentMenuLevel].CurrentTopIndex;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
