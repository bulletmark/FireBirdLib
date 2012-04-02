#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyColorPatch(int ItemIndex, dword Color)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems) || (ItemIndex < 0)) return FALSE;

  pMenu->Item[ItemIndex].ColorPatch = Color;

  ListDirty = TRUE;

  return TRUE;
}
