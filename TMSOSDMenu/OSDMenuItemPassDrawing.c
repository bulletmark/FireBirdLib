#include "FBLib_TMSOSDMenu.h"

bool OSDMenuItemPassDrawing (int ItemIndex, bool VisibleName, bool VisibleValue)
{
  tMenu                *pMenu;
  bool                  result = FALSE;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (ItemIndex >= 0 && ItemIndex < pMenu->NrItems)
  {
    pMenu->Item[ItemIndex].passDrawing = TRUE;
    pMenu->Item[ItemIndex].drawName  = VisibleName;
    pMenu->Item[ItemIndex].drawValue = VisibleValue;
    result = TRUE;
  }

  TRACEEXIT();

  return result;
}
