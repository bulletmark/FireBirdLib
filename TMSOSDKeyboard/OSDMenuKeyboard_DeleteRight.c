#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_DeleteRight(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_DeleteRight");
  #endif

  if(OSDMenuKeyboard_CursorPosition < (int)strlenUC(OSDMenuKeyboard_StringVar))
  {
    DeleteAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, 1);
    OSDMenuKeyboard_Draw();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
