#include "FBLib_TMSOSDMenu.h"

bool OSDMenuListBoxInitialize (bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, const char *Title, dword x, dword width, bool OSDUpdate)
{
  tMenu                *pMenu;

  TRACEENTER();

 if (width <= (dword) LISTBOX_ADDITIONAL_WIDTH + 20 || x + width > 720)
  {
    TRACEEXIT();
    return FALSE;
  }

  OSDMenuPush();
  OSDDirty = OSDUpdate;

  OSDMenuInit(AllowScrollingOfLongText, HasValueColumn, NumberedItems, ScrollLoop, Title, NULL);

  pMenu = &Menu[CurrentMenuLevel];
  pMenu->OSDMenuDisplayMode = OMDM_ListBox;
  pMenu->XPos = x + LISTBOX_OFFSET_TO_X;
  pMenu->Width = width - LISTBOX_ADDITIONAL_WIDTH;

  OSDMenuButtonsClear();

  TRACEEXIT();

  return TRUE;
}
