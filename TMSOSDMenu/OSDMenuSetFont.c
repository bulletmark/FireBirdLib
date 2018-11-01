#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetFont(tFontDataUC *LeftTitle, tFontDataUC *RightTitle, tFontDataUC *ListNumber, tFontDataUC *ListName, tFontDataUC *ListValue, tFontDataUC *Buttons, tFontDataUC *Memo)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(LeftTitle)
  {
    pMenu->FontLeftTitle = LeftTitle;
    TitleDirty = TRUE;
  }

  if(RightTitle)
  {
    pMenu->FontRightTitle = RightTitle;
    TitleDirty = TRUE;
  }

  if(ListNumber)
  {
    pMenu->FontListLineNumber = ListNumber;
    ListDirty = TRUE;
  }

  if(ListName)
  {
    pMenu->FontListNameColumn = ListName;
    ListDirty = TRUE;
  }

  if(ListValue)
  {
    pMenu->FontListValueColumn = ListValue;
    ListDirty = TRUE;
  }

  if(Buttons)
  {
    pMenu->FontButtons = Buttons;
    ButtonsDirty = TRUE;
  }

  if(Memo)
  {
    pMenu->FontMemo = Memo;
    ListDirty = TRUE;
  }

  TRACEEXIT();
}
