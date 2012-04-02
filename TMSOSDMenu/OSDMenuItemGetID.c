#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetID(int ItemIndex)
{
  if((ItemIndex < 0) || (ItemIndex >= Menu[CurrentMenuLevel].NrItems)) return 0;

  return Menu[CurrentMenuLevel].Item[ItemIndex].ID;
}
