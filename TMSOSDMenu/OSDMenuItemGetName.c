#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetName(int ItemIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetName");
  #endif

  char *ret;

  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems))
    ret = NULL;
  else
    ret = Menu[CurrentMenuLevel].Item[ItemIndex].Name;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
