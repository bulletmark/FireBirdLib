#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_Show(void)
{
  TRACEENTER;

  OSDMenuKeyboard_EventHandler(NULL, NULL, NULL);

  TRACEEXIT;
}
