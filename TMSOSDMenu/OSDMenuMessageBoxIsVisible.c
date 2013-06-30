#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuMessageBoxIsVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxIsVisible");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (MessageBoxOSDRgn != 0);
}
