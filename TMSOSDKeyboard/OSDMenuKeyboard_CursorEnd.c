#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorEnd(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_CursorEnd");
  #endif

  OSDMenuKeyboard_CursorPosition = strlenUC(OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Draw();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
