#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxDoNotEnterNormalMode(bool DoNotEnterNormalMode)
{
  TRACEENTER;

  MessageBoxNoNormalMode = DoNotEnterNormalMode;

  TRACEEXIT;
}
