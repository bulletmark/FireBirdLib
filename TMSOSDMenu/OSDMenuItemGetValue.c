#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetValue(int ItemIndex)
{
  TRACEENTER;

  char *ret;

  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems))
    ret = NULL;
  else
    ret = Menu[CurrentMenuLevel].Item[ItemIndex].Value;

  TRACEEXIT;
  return ret;
}
