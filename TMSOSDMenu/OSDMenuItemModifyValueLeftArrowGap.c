#include "FBLib_TMSOSDMenu.h"

void OSDMenuItemModifyValueLeftArrowGap (int NewGapWidth)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (NewGapWidth >= -30)
    pMenu->ValueXOffset = NewGapWidth;
  else
    pMenu->ValueXOffset = 15;

  ListDirty = TRUE;

  TRACEEXIT();
}
