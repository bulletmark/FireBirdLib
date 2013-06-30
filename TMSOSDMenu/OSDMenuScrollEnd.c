#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollEnd(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuScrollEnd");
  #endif

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindPreviousSelectableEntry(pMenu->NrItems);
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
