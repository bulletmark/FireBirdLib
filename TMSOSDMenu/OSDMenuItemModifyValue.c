#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuItemModifyValue(int ItemIndex, const char *Text)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if((ItemIndex < 0) || (ItemIndex >= pMenu->NrItems))
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!Text)
  {
    TRACEEXIT();
    return FALSE;
  }

  strncpy(pMenu->Item[ItemIndex].Value, Text, ITEMNAMESIZE);
  pMenu->Item[ItemIndex].Value[ITEMNAMESIZE - 1] = '\0';

  ListDirty = TRUE;

  TRACEEXIT();
  return TRUE;
}
