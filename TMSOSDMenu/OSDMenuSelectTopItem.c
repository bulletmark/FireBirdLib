#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuSelectTopItem(int TopIndex)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->NrItems == 0) return FALSE;
  if(TopIndex < 0) TopIndex = 0;
  if(TopIndex >= (int)pMenu->NrItems) TopIndex = (int)pMenu->NrItems - 1;

  if(TopIndex != (int)pMenu->CurrentTopIndex)
  {
    pMenu->CurrentTopIndex = TopIndex;
    ListDirty = TRUE;
  }

  return TRUE;
}
