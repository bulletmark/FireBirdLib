#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetCursor(tCursorType CursorType)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuSetCursor");
  #endif

  MenuCursorType = CursorType;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
