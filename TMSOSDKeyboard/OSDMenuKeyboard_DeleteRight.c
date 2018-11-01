#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_DeleteRight(void)
{
  TRACEENTER();

  if(OSDMenuKeyboard_CursorPosition < (int)strlenUC(OSDMenuKeyboard_StringVar))
  {
    DeleteAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, 1);
    OSDMenuKeyboard_Draw();
  }

  TRACEEXIT();
}
