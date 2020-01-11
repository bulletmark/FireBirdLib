#include "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyNameColor (int ItemIndex, dword Color)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if(ItemIndex < 0 || ItemIndex >= pMenu->NrItems)
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].NameColor = Color;

  ListDirty = TRUE;

  TRACEEXIT();

  return TRUE;
}
