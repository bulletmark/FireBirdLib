#include "FBLib_TMSOSDMenu.h"

void OSDMenuSetMemo (bool SelectionAlwaysOnTop)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  pMenu->AllowScrollingOfLongText = FALSE;
  pMenu->HasValueColumn = FALSE;
  pMenu->NumberedItems = FALSE;
  pMenu->OSDMenuDisplayMode = (SelectionAlwaysOnTop ? OMDM_Memo : OMDM_Text);
  pMenu->XPos = 60;
  pMenu->Width = 600;
  pMenu->NrLines = 15;

  TRACEEXIT();
}
