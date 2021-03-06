#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollPageDown(void)
{
  TRACEENTER();

  tMenu                *pMenu;
  int                   ret, x;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->CurrentSelection == (pMenu->NrItems - 1)) && pMenu->ScrollLoop)
  {
    ret = OSDMenuFindNextSelectableEntry(-1);
  }
  else if(pMenu->CurrentSelection == (pMenu->CurrentTopIndex + pMenu->NrLines - 1))
  {
    x = pMenu->CurrentSelection + pMenu->NrLines - 1;
    if(x >= pMenu->NrItems) x = pMenu->NrItems - 2;
    if(x < (pMenu->NrItems - 1))
      ret = OSDMenuFindNextSelectableEntry(x);
    else
      ret = x;
  }
  else
  {
    x = pMenu->CurrentSelection + pMenu->NrLines - 2 - (pMenu->CurrentSelection - pMenu->CurrentTopIndex);
    if(x >= pMenu->NrItems) x = pMenu->NrItems - 2;
    ret = OSDMenuFindNextSelectableEntry(x);
  }

  if(ret == -1)
  {
    TRACEEXIT();
    return -1;
  }

  pMenu->CurrentSelection = ret;
  ListDirty = TRUE;

  TRACEEXIT();
  return ret;
}
