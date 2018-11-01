#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetCursor(tCursorType CursorType)
{
  TRACEENTER();

  MenuCursorType = CursorType;

  TRACEEXIT();
}
