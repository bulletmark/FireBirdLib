#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorEnd(void)
{
  OSDMenuKeyboard_CursorPosition = strlen(OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Draw();
}
