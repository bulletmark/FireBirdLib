#include                "FBLib_TMSOSDKeyboard.h"

bool OSDMenuKeyboard_isVisible(void)
{
  TRACEENTER;

  bool ret = (OSDMenuKeyboard_rgn != 0);

  TRACEEXIT;

  return ret;
}
