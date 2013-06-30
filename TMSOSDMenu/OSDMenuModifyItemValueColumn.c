#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemValueColumn(bool HasValueColumn)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyItemValueColumn");
  #endif

  Menu[CurrentMenuLevel].HasValueColumn = HasValueColumn;
  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
