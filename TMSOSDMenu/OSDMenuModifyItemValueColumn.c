#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemValueColumn(bool HasValueColumn)
{
  Menu[CurrentMenuLevel].HasValueColumn = HasValueColumn;
  ListDirty = TRUE;
}
