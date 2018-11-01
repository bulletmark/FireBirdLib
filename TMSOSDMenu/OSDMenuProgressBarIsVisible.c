#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuProgressBarIsVisible(void)
{
  TRACEENTER();

  TRACEEXIT();
  return (ProgressBarOSDRgn != 0);
}
