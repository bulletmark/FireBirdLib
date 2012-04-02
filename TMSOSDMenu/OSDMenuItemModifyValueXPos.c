#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemModifyValueXPos(dword NewValueXPos)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(NewValueXPos)
    pMenu->ValueXPos = NewValueXPos;
  else
    pMenu->ValueXPos = 350;

  ListDirty = TRUE;
}
