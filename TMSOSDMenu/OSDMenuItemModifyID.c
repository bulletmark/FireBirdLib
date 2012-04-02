#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyID(int ItemIndex, dword ID)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems)) return FALSE;

  pMenu->Item[ItemIndex].ID = ID;

  return TRUE;
}
