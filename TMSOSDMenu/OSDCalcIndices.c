#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDCalcIndices(void)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  //if TopIndex or SelectionIndex has changed, make list dirty
  //TODO: Verhalten der Originalbox. Wo wird gescrollt?

  if(pMenu->OSDMenuDisplayMode == OMDM_Memo)
  {
    pMenu->CurrentTopIndex = pMenu->CurrentSelection;
  }
  else
  {
    if(pMenu->CurrentSelection < pMenu->CurrentTopIndex)       pMenu->CurrentTopIndex = pMenu->CurrentSelection;
    if(pMenu->CurrentSelection > (pMenu->CurrentTopIndex + 9)) pMenu->CurrentTopIndex = pMenu->CurrentSelection - 9;
  }
}
