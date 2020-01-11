#include "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_SetCursor (tKeyboardCursor KeyboardCursor)
{
  TRACEENTER();

  KeyboardCursorType = KeyboardCursor;

  TRACEEXIT();
}
