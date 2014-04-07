#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_SaveAndFinish(void)
{
  TRACEENTER();

  strcpy(OSDMenuKeyboard_StringVarOrig, OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Finish();

  TRACEEXIT();
}
