#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyScrollLoop(bool ScrollLoop)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyScrollLoop");
  #endif

  Menu[CurrentMenuLevel].ScrollLoop = ScrollLoop;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
