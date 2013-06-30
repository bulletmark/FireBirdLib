#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSaveMyRegion(word Rgn)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuSaveMyRegion");
  #endif

  MyOSDRgn = Rgn;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
