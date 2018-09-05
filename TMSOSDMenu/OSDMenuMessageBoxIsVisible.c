#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuMessageBoxIsVisible(void)
{
  TRACEENTER;

  TRACEEXIT;
  return (MessageBoxOSDRgn != 0);
}
