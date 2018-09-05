#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollUp(void)
{
  TRACEENTER;

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindPreviousSelectableEntry(pMenu->CurrentSelection);
  if(ret == -1)
  {
    TRACEEXIT;
    return -1;
  }

  pMenu->CurrentSelection = ret;
  ListDirty = TRUE;

  TRACEEXIT;
  return ret;
}
