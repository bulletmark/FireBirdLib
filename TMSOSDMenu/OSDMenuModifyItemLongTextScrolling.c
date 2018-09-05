#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemLongTextScrolling(bool AllowScrollingOfLongText)
{
  TRACEENTER;

  Menu[CurrentMenuLevel].AllowScrollingOfLongText = AllowScrollingOfLongText;

  TRACEEXIT;
}
