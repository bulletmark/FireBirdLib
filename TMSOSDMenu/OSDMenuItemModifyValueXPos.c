#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemModifyValueXPos(dword NewValueXPos)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemModifyValueXPos");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(NewValueXPos)
    pMenu->ValueXPos = NewValueXPos;
  else
    pMenu->ValueXPos = 350;

  ListDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
