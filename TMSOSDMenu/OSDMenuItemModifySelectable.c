#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifySelectable(int ItemIndex, bool Selectable)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemModifySelectable");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  pMenu->Item[ItemIndex].Selectable = Selectable;

  if((pMenu->CurrentSelection == ItemIndex) && (Selectable == FALSE))
  {
    //TODO: check if there is at least one selectable item
    //  scroll up until hit
    //  else scroll down until hit
    if(pMenu->CurrentSelection > 0)
      pMenu->CurrentSelection--;
    else
      pMenu->CurrentSelection++;

    ListDirty = TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
