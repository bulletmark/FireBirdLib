#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyColorPatch(int ItemIndex, dword Color)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems) || (ItemIndex < 0))
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].ColorPatch = Color;

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
