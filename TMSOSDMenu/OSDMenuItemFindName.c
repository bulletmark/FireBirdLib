#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

int OSDMenuItemFindName(char *Text)
{
  tMenu                *pMenu;
  int                   i;

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->NrItems == 0) return -1;
  if(!Text || !Text[0]) return -1;

  for(i = 0; i < pMenu->NrItems; i++)
    if(strcmp(pMenu->Item[i].Name, Text) == 0) return i;

  return -1;
}
