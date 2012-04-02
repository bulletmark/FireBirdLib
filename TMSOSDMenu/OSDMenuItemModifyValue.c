#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyValue(int ItemIndex, char *Text)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((pMenu->NrItems == 0) || (ItemIndex >= pMenu->NrItems)) return FALSE;
  if(!Text) return FALSE;

  strncpy(pMenu->Item[ItemIndex].Value, Text, ITEMNAMESIZE);
  pMenu->Item[ItemIndex].Value[ITEMNAMESIZE - 1] = '\0';

  //TODO: only when in visible area
  ListDirty = TRUE;

  return TRUE;
}
