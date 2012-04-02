#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorRight(void)
{
  if(OSDMenuKeyboard_CursorPosition < (int)strlen(OSDMenuKeyboard_StringVar))
  {
    OSDMenuKeyboard_CursorPosition++;
    OSDMenuKeyboard_Draw();
  }
}
