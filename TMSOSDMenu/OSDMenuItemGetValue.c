#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetValue(int ItemIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemGetValue");
  #endif

  char *ret;

  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems))
    ret = NULL;
  else
    ret = Menu[CurrentMenuLevel].Item[ItemIndex].Value;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
