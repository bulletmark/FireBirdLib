#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuSetFont(tFontData *LeftTitle, tFontData *RightTitle, tFontData *ListNumber, tFontData *ListName, tFontData *ListValue, tFontData *Buttons, tFontData *Memo)
{
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
}
