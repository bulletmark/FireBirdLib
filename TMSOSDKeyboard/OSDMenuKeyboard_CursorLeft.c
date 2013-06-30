#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorLeft(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_CursorLeft");
  #endif

  if(OSDMenuKeyboard_CursorPosition > 0)
  {
    OSDMenuKeyboard_CursorPosition--;
    OSDMenuKeyboard_Draw();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
