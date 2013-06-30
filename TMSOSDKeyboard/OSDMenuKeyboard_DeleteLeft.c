#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_DeleteLeft(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_DeleteLeft");
  #endif

  if(OSDMenuKeyboard_CursorPosition > 0)
  {
    OSDMenuKeyboard_CursorPosition--;
    DeleteAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, 1);
    OSDMenuKeyboard_Draw();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
