#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemSortID(bool Ascending)
{
  int                   i, j, NrItems;
  tItem                 TempItem;
  dword                 ID1, ID2;
  bool                  Swap;

  NrItems = Menu[CurrentMenuLevel].NrItems;

  for(i = 0; i < NrItems - 1; i++)
  {
    for(j = i + 1; j < NrItems; j++)
    {
      ID1 = Menu[CurrentMenuLevel].Item[i].ID;
      ID2 = Menu[CurrentMenuLevel].Item[j].ID;

      switch(Ascending ? 1 : 0)
      {
        case 0: Swap = (ID1 < ID2); break;
        case 1: Swap = (ID1 > ID2); break;
        default:
          Swap = FALSE;
          break;
      }

      if(Swap)
      {
        memcpy(&TempItem, &Menu[CurrentMenuLevel].Item[i], sizeof(tItem));
        memcpy(&Menu[CurrentMenuLevel].Item[i], &Menu[CurrentMenuLevel].Item[j], sizeof(tItem));
        memcpy(&Menu[CurrentMenuLevel].Item[j], &TempItem, sizeof(tItem));
      }
    }
  }

  ListDirty = TRUE;
}
