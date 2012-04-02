#include                "FBLib_TMSOSDMenu.h"

char *OSDMenuItemGetValue(int ItemIndex)
{
  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems)) return NULL;

  return Menu[CurrentMenuLevel].Item[ItemIndex].Value;
}
