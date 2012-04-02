#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_SaveAndFinish(void)
{
  strcpy(OSDMenuKeyboard_StringVarOrig, OSDMenuKeyboard_StringVar);
  OSDMenuKeyboard_Finish();
}
