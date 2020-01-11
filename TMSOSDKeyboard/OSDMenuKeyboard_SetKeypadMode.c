#include "FBLib_TMSOSDKeyboard.h"

bool OSDMenuKeyboard_SetKeypadMode (tKeyPadMode mode)
{
  bool result = FALSE;

  TRACEENTER();

  if ((int) mode >= KPM_Standard && mode < KPM_NrModes && *Keypad[mode][0] != 0)
  {
    KeyPadMode = mode;
    result = TRUE;
  }

  TRACEEXIT();

  return result;
}
