#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuProgressBarIsVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuProgressBarIsVisible");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (ProgressBarOSDRgn != 0);
}
