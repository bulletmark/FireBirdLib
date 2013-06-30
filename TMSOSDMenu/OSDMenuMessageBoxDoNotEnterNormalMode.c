#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxDoNotEnterNormalMode(bool DoNotEnterNormalMode)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxDoNotEnterNormalMode");
  #endif

  MessageBoxNoNormalMode = DoNotEnterNormalMode;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
