#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyColorPatch(int ItemIndex, dword Color)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemModifyColorPatch");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems) || (ItemIndex < 0))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  pMenu->Item[ItemIndex].ColorPatch = Color;

  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
