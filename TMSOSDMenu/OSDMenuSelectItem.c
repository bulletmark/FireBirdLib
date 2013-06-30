#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuSelectItem(int ItemIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuSelectItem");
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

  if(ItemIndex < 0) ItemIndex = 0;
  if(ItemIndex >= (int)pMenu->NrItems) ItemIndex = (int)pMenu->NrItems - 1;

  if(ItemIndex != (int)pMenu->CurrentSelection)
  {
    if(!pMenu->Item[ItemIndex].Selectable)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return FALSE;
    }

    pMenu->CurrentSelection = ItemIndex;
    ListDirty = TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
