#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyNameIcon(int ItemIndex, TYPE_GrData *pNameIconGd)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems)) return FALSE;

  pMenu->Item[ItemIndex].pNameIconGd = pNameIconGd;

  //TODO: only when in visible area
  ListDirty = TRUE;

  return TRUE;
}
