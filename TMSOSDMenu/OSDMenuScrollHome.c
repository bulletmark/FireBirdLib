#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollHome(void)
{
  TRACEENTER;

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindNextSelectableEntry(-1);
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
