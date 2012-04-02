#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemLongTextScrolling(bool AllowScrollingOfLongText)
{
  Menu[CurrentMenuLevel].AllowScrollingOfLongText = AllowScrollingOfLongText;
}
