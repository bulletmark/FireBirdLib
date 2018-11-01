#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetID(int ItemIndex)
{
  TRACEENTER();

  dword ret;

  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems))
    ret = 0;
  else
    ret = Menu[CurrentMenuLevel].Item[ItemIndex].ID;

  TRACEEXIT();
  return ret;
}
