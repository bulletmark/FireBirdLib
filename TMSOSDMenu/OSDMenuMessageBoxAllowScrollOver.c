#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxAllowScrollOver(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxAllowScrollOver");
  #endif

  MessageBoxAllowScrollOver = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
