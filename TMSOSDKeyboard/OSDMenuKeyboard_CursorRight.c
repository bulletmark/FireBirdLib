#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorRight(void)
{
  TRACEENTER;

  if(OSDMenuKeyboard_CursorPosition < (int)strlenUC(OSDMenuKeyboard_StringVar))
  {
    OSDMenuKeyboard_CursorPosition++;
    OSDMenuKeyboard_Draw();
  }

  TRACEEXIT;
}
