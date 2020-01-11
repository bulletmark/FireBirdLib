#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetCallback(void *OSDCallbackRoutine)
{
  TRACEENTER();

  Menu[CurrentMenuLevel].CallbackProcedure = OSDCallbackRoutine;

  TRACEEXIT();
}
