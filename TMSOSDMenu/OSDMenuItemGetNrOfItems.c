#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetNrOfItems(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetNrOfItems");
  #endif

  dword ret;

  ret = Menu[CurrentMenuLevel].NrItems;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
