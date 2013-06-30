#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetCallback(void *OSDCallbackRoutine)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuSetCallback");
  #endif

  CallbackProcedure = OSDCallbackRoutine;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
