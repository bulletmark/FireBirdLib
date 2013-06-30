#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_Destroy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_Destroy");
  #endif

  OSDMenuKeyboard_Finish();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
