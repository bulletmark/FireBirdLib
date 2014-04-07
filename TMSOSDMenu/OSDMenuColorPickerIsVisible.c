#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuColorPickerIsVisible(void)
{
  TRACEENTER();

  TRACEEXIT();
  return (ColorPickerOSDRgn != 0);
}
