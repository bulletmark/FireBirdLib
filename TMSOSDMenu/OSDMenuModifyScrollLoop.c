#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyScrollLoop(bool ScrollLoop)
{
  TRACEENTER();

  Menu[CurrentMenuLevel].ScrollLoop = ScrollLoop;

  TRACEEXIT();
}
