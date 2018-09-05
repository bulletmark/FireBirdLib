#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyNameIcon(int ItemIndex, TYPE_GrData *pNameIconGd)
{
  TRACEENTER;

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT;
    return FALSE;
  }

  pMenu->Item[ItemIndex].pNameIconGd = pNameIconGd;

  ListDirty = TRUE;

  TRACEEXIT;
  return TRUE;
}
