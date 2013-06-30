#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuSelectTopItem(int TopIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuSelectTopItem");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->NrItems == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(TopIndex < 0) TopIndex = 0;
  if(TopIndex >= (int)pMenu->NrItems) TopIndex = (int)pMenu->NrItems - 1;

  if(TopIndex != (int)pMenu->CurrentTopIndex)
  {
    pMenu->CurrentTopIndex = TopIndex;
    ListDirty = TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
