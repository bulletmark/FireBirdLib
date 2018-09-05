#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollDown(void)
{
  TRACEENTER;

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindNextSelectableEntry(pMenu->CurrentSelection);
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
