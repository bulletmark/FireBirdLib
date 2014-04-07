#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyID(int ItemIndex, dword ID)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].ID = ID;

  TRACEEXIT();
  return TRUE;
}
