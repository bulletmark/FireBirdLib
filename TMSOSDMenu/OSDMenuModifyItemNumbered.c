#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemNumbered(bool NumberedItems)
{
  TRACEENTER();

  Menu[CurrentMenuLevel].NumberedItems = NumberedItems;
  ListDirty = TRUE;

  TRACEEXIT();
}
