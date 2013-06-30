#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuInfoBoxIsVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuInfoBoxIsVisible");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (InfoBoxOSDRgn != 0);
}
