#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyCustomIndex(int ItemIndex, int CustomIndex)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((ItemIndex < 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].CustomIndex = CustomIndex;

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
