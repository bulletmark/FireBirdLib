#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyID(int ItemIndex, dword ID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemModifyID");
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

  pMenu->Item[ItemIndex].ID = ID;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
