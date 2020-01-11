#include "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyValueArrows (int ItemIndex, bool ValueArrows)
{
  tMenu                *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (ItemIndex < 0 || ItemIndex >= pMenu->NrItems)
  {
    TRACEEXIT();
    return FALSE;
  }

  pMenu->Item[ItemIndex].ValueArrows = ValueArrows;

  ListDirty = TRUE;

  TRACEEXIT();

  return TRUE;
}
