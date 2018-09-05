#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemValueColumn(bool HasValueColumn)
{
  TRACEENTER;

  Menu[CurrentMenuLevel].HasValueColumn = HasValueColumn;
  ListDirty = TRUE;

  TRACEEXIT;
}
