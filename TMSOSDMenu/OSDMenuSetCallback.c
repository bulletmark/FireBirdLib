#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetCallback(void *OSDCallbackRoutine)
{
  TRACEENTER;

  CallbackProcedure = OSDCallbackRoutine;

  TRACEEXIT;
}
