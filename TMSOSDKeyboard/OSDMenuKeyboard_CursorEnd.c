#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_CursorEnd(void)
{
  TRACEENTER;

  OSDMenuKeyboard_CursorPosition = strlenUC(OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Draw();

  TRACEEXIT;
}
