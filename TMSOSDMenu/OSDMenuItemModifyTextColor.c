#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyTextColor(int ItemIndex, dword Color)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((ItemIndex < 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].TextColor = Color;

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
