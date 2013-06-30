#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyNameIcon(int ItemIndex, TYPE_GrData *pNameIconGd)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemModifyNameIcon");
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

  pMenu->Item[ItemIndex].pNameIconGd = pNameIconGd;

  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
