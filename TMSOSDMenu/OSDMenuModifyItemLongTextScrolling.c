#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemLongTextScrolling(bool AllowScrollingOfLongText)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyItemLongTextScrolling");
  #endif

  Menu[CurrentMenuLevel].AllowScrollingOfLongText = AllowScrollingOfLongText;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
