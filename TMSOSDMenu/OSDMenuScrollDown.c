#include                "FBLib_TMSOSDMenu.h"

int OSDMenuScrollDown(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuScrollDown");
  #endif

  tMenu                *pMenu;
  int                   ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = OSDMenuFindNextSelectableEntry(pMenu->CurrentSelection);
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
