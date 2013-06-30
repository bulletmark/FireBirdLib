#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollUp(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuScrollUp");
  #endif

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindPreviousSelectableEntry(pMenu->CurrentSelection);
  if(ret == -1)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return -1;
  }

  pMenu->CurrentSelection = ret;
  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
