#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollPageUp(void)
{
  tMenu                *pMenu;
  int                   ret, x;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->CurrentSelection == 0) && pMenu->ScrollLoop)
  {
    ret = OSDMenuFindPreviousSelectableEntry(pMenu->NrItems);
  }
  else if(pMenu->CurrentSelection == pMenu->CurrentTopIndex)
  {
    x = pMenu->CurrentSelection - 10;
    if(x < 0) x = 0;
    ret = OSDMenuFindPreviousSelectableEntry(x + 1);
  }
  else
    ret = OSDMenuFindPreviousSelectableEntry(pMenu->CurrentTopIndex + 1);

  if(ret == -1) return -1;

  pMenu->CurrentSelection = ret;
  ListDirty = TRUE;

  return ret;
}
