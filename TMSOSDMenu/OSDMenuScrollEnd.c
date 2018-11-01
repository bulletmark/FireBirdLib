#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollEnd(void)
{
  TRACEENTER();

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindPreviousSelectableEntry(pMenu->NrItems);
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
