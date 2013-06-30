#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuColorPickerIsVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuColorPickerIsVisible");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (ColorPickerOSDRgn != 0);
}
