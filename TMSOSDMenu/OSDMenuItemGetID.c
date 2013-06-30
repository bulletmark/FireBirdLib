#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetID(int ItemIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetID");
  #endif

  dword ret;

  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems))
    ret = 0;
  else
    ret = Menu[CurrentMenuLevel].Item[ItemIndex].ID;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
