#include "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetTextColor (int ItemIndex)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if(ItemIndex < 0 || ItemIndex >= pMenu->NrItems)
  {
    TRACEEXIT();
    return 0;
  }

  TRACEEXIT();

  return pMenu->Item[ItemIndex].TextColor;
}
