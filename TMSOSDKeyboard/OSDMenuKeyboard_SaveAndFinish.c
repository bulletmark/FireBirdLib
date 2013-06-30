#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_SaveAndFinish(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_SaveAndFinish");
  #endif

  strcpy(OSDMenuKeyboard_StringVarOrig, OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Finish();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
