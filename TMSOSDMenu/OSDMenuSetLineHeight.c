#include "FBLib_TMSOSDMenu.h"

void OSDMenuSetLineHeight (tLineHeight type)
{
  tMenu *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  pMenu->FontLeftTitle  = &OSDMenuFont_20;
  pMenu->FontRightTitle = &OSDMenuFont_16;
  pMenu->FontButtons    = &OSDMenuFont_12;

  switch (type)
  {
    case LH_Normal:
    case LH_Small:
      pMenu->FontListLineNumber  = &OSDMenuFont_14;
      pMenu->FontListNameColumn  = &OSDMenuFont_14;
      pMenu->FontListValueColumn = &OSDMenuFont_14;
      pMenu->FontMemo            = &OSDMenuFont_14;
      pMenu->NrLines = (type == LH_Normal && pMenu->OSDMenuDisplayMode == OMDM_Standard ? 10 : 15);
      ListDirty = TRUE;
      break;

    case LH_Tiny:
      pMenu->FontListLineNumber  = &OSDMenuFont_12;
      pMenu->FontListNameColumn  = &OSDMenuFont_12;
      pMenu->FontListValueColumn = &OSDMenuFont_12;
      pMenu->FontMemo            = &OSDMenuFont_12;
      pMenu->NrLines = 18;
      ListDirty = TRUE;
      break;

    default:
      break;
  }

  if (pMenu->OSDMenuDisplayMode == OMDM_Standard)
  {
    OSDDirty = TRUE;
    OSDMenuLastCursor = LCT_NRCURSORS;
  }

  if (pMenu->OSDMenuDisplayMode == OMDM_Memo || pMenu->OSDMenuDisplayMode == OMDM_Text) OSDMemoFormatText();

  TRACEEXIT();
}
