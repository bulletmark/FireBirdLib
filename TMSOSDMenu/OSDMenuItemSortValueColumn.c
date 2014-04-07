#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuItemSortValueColumn(bool Ascending, bool CaseSensitive)
{
  TRACEENTER();

  int                   i, j, NrItems;
  tItem                 TempItem;
  char                 *p1, *p2;
  bool                  Swap;

  NrItems = Menu[CurrentMenuLevel].NrItems;

  for(i = 0; i < NrItems - 1; i++)
  {
    for(j = i + 1; j < NrItems; j++)
    {
      p1 = Menu[CurrentMenuLevel].Item[i].Value;
      while(*p1 && (*p1 < ' '))
        p1++;

      p2 = Menu[CurrentMenuLevel].Item[j].Value;
      while(*p2 && (*p2 < ' '))
        p2++;

      switch((Ascending ? 1 : 0) + (CaseSensitive ? 2 : 0))
      {
        case 0: Swap = (strcasecmp(p1, p2) < 0); break;
        case 1: Swap = (strcasecmp(p1, p2) > 0); break;
        case 2: Swap = (strcmp(p1, p2) < 0); break;
        case 3: Swap = (strcmp(p1, p2) > 0); break;
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

  TRACEEXIT();
}
