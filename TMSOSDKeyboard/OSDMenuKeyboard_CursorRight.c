#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorRight(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_CursorRight");
  #endif

  if(OSDMenuKeyboard_CursorPosition < (int)strlenUC(OSDMenuKeyboard_StringVar))
  {
    OSDMenuKeyboard_CursorPosition++;
    OSDMenuKeyboard_Draw();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
