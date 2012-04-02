#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_DeleteLeft(void)
{
  if(OSDMenuKeyboard_CursorPosition > 0)
  {
    OSDMenuKeyboard_CursorPosition--;
    DeleteAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, 1);
    OSDMenuKeyboard_Draw();
  }
}
