#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyName(int ItemIndex, char *Text)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems)) return FALSE;
  if(!Text || !Text[0]) return FALSE;

  strncpy(pMenu->Item[ItemIndex].Name, Text, ITEMNAMESIZE);
  pMenu->Item[ItemIndex].Name[ITEMNAMESIZE - 1] = '\0';

  //TODO: only when in visible area
  ListDirty = TRUE;

  return TRUE;
}
