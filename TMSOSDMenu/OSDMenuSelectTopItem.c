#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuSelectTopItem(int TopIndex)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->NrItems == 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(TopIndex < 0) TopIndex = 0;
  if(TopIndex >= (int)pMenu->NrItems) TopIndex = (int)pMenu->NrItems - 1;

  if(TopIndex != (int)pMenu->CurrentTopIndex)
  {
    pMenu->CurrentTopIndex = TopIndex;
    ListDirty = TRUE;
  }

  TRACEEXIT();
  return TRUE;
}
