#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuIsVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuIsVisible");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return OSDRgn != 0;
}
