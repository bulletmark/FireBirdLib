#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemNumbered(bool NumberedItems)
{
  Menu[CurrentMenuLevel].NumberedItems = NumberedItems;
  ListDirty = TRUE;
}
