#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyName(int ItemIndex, const char *Text)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((ItemIndex < 0) || (ItemIndex >= pMenu->NrItems) || !Text || !Text[0])
  {
    TRACEEXIT();
    return FALSE;
  }

  strncpy(pMenu->Item[ItemIndex].Name, Text, ITEMNAMESIZE);
  pMenu->Item[ItemIndex].Name[ITEMNAMESIZE - 1] = '\0';

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
