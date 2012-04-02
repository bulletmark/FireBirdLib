#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyValueIcon(int ItemIndex, TYPE_GrData *pValueIconGd)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems)) return FALSE;

  pMenu->Item[ItemIndex].pValueIconGd = pValueIconGd;

  //TODO: only when in visible area
  ListDirty = TRUE;

  return TRUE;
}
