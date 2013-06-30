#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuColorPickerColor(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuColorPickerColor");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ColorPickerColor;
}
