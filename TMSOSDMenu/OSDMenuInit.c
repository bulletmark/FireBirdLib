#include <string.h>
#include "FBLib_TMSOSDMenu.h"

word                    OSDRgn, MyOSDRgn, OSDMenuSelectionBarRgn;
bool                    OSDDirty, TitleDirty, ListDirty, ButtonsDirty, LogoDirty;
tMenu                   Menu[NRMENULEVELS];
dword                   CurrentMenuLevel;
dword                   ButtonColor;
tCursorType             MenuCursorType;
tOSDMenuLastCursorType  OSDMenuLastCursor = LCT_NRCURSORS;

word                    InfoBoxOSDRgn;
dword                   InfoBoxTimeOut;
byte                   *InfoBoxSaveArea;
dword                   InfoBoxSaveAreaX, InfoBoxSaveAreaY;
bool                    InfoBoxExitButton;

word                    MessageBoxOSDRgn;
tMessageBox             MessageBox;
bool                    MessageBoxNoNormalMode;
bool                    MessageBoxAllowScrollOver;

word                    ProgressBarOSDRgn;
word                    ProgressBarFullRgn;
dword                   ProgressBarLastValue = 0xfff;

word                    ColorPickerOSDRgn;
dword                   ColorPickerColor;
dword                   ColorPickerDefaultColor;
tCurrentColorSelected   CurrentColorSelected;
int                     ColorPickerLastCursorRed, ColorPickerLastCursorGreen, ColorPickerLastCursorBlue;

word                    WaitSpinnerRgn;
int                     WaitSpinnerIndex;
dword                   WaitSpinnerTimeout;

dword                   LastUnprocessedOSDMenuKey;

tFontDataUC             OSDMenuFont_10;
tFontDataUC             OSDMenuFont_12;
tFontDataUC             OSDMenuFont_14;
tFontDataUC             OSDMenuFont_16;
tFontDataUC             OSDMenuFont_18;
tFontDataUC             OSDMenuFont_20;
tFontDataUC             OSDMenuFont_20B;

void OSDMenuInit (bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, const char *TitleLeft, const char *TitleRight)
{
  tMenu                *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  memset(pMenu, 0, sizeof(tMenu));

  OSDMenuLoadStdFonts();

  pMenu->OSDMenuDisplayMode = OMDM_Standard;
  pMenu->AllowScrollingOfLongText = AllowScrollingOfLongText;
  pMenu->HasValueColumn = HasValueColumn;
  pMenu->NumberedItems = NumberedItems;
  pMenu->ScrollLoop = ScrollLoop;
  pMenu->XPos = 60;
  pMenu->Width = 600;
  pMenu->ValueXPos = 350;
  pMenu->ValueXOffset = 15;
  pMenu->hasValueArrows = FALSE;
  pMenu->MaxItems = 30;
  pMenu->Item = TAP_MemAlloc(pMenu->MaxItems * sizeof(tItem));
  memset(&pMenu->Item[0], 0, pMenu->MaxItems * sizeof(tItem));

  OSDMenuSetLineHeight(LH_Normal);

  if (TitleLeft) strncpy(pMenu->TitleLeft, TitleLeft, STDSTRINGSIZE);
  else pMenu->TitleLeft[0] = '\0';

  pMenu->TitleLeft[STDSTRINGSIZE - 1] = '\0';

  if (TitleRight) strncpy(pMenu->TitleRight, TitleRight, STDSTRINGSIZE);
  else pMenu->TitleRight[0] = '\0';

  pMenu->TitleRight[STDSTRINGSIZE - 1] = '\0';

  MenuCursorType = CT_Standard;

  TRACEEXIT();
}
