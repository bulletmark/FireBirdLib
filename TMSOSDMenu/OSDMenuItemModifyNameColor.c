#include "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyNameColor (int ItemIndex, dword Color)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->NrItems == 0 || ItemIndex >= pMenu->NrItems || ItemIndex < 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].NameColor = Color;

  ListDirty = TRUE;

  TRACEEXIT();

  return TRUE;
}
