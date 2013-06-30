#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuButtonColor(dword Color)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuButtonColor");
  #endif

  ButtonColor = (Color != 0 ? Color : RGB(230, 230, 250));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
