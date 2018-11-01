#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyValueIcon(int ItemIndex, TYPE_GrData *pValueIconGd)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].pValueIconGd = pValueIconGd;

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
