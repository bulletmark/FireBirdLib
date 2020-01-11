#include <string.h>
#include "FBLib_TMSOSDKeyboard.h"

bool OSDMenuKeyboard_ChangeKeypad (tKeyPadMode mode, char keypad[26][4])
{
  bool result = FALSE;

  TRACEENTER();

  if (mode > KPM_CAPS && mode < KPM_NrModes)
  {
    if (keypad) memcpy(Keypad[mode], keypad, 26 << 2);
    else *Keypad[mode][0] = 0;

    result = TRUE;
  }

  TRACEEXIT();

  return result;
}
