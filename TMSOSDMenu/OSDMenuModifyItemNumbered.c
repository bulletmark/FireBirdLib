#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyItemNumbered(bool NumberedItems)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyItemNumbered");
  #endif

  Menu[CurrentMenuLevel].NumberedItems = NumberedItems;
  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
