#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorLeft(void)
{
  if(OSDMenuKeyboard_CursorPosition > 0)
  {
    OSDMenuKeyboard_CursorPosition--;
    OSDMenuKeyboard_Draw();
  }
}
