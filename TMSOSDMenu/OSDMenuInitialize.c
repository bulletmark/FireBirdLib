#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_TMSOSDMenu.h"

word                    OSDRgn = 0, MyOSDRgn = 0, OSDMenuSelectionBarRgn = 0;
bool                    OSDDirty, TitleDirty, ListDirty, ButtonsDirty, LogoDirty;
tMenu                   Menu[NRMENULEVELS];
dword                   CurrentMenuLevel = 0;
dword                   ButtonColor;
tCursorType             MenuCursorType;
tOSDMenuLastCursorType    OSDMenuLastCursor = LCT_NRCURSORS;

word                    InfoBoxOSDRgn = 0;
dword                   InfoBoxTimeOut = 0;
byte                   *InfoBoxSaveArea = NULL;
dword                   InfoBoxSaveAreaX, InfoBoxSaveAreaY;

word                    MessageBoxOSDRgn = 0;
tMessageBox             MessageBox;
bool                    MessageBoxNoNormalMode = FALSE;
bool                    MessageBoxAllowScrollOver = FALSE;

word                    ProgressBarOSDRgn = 0;
word                    ProgressBarFullRgn = 0;
dword                   ProgressBarLastValue = 0xfff;

word                    ColorPickerOSDRgn = 0;
dword                   ColorPickerColor;
dword                   ColorPickerDefaultColor;
tCurrentColorSelected   CurrentColorSelected;
int                     ColorPickerLastCursorRed, ColorPickerLastCursorGreen, ColorPickerLastCursorBlue;

word                    WaitSpinnerRgn = 0;
int                     WaitSpinnerIndex = 0;
dword                   WaitSpinnerTimeout = 0;

dword                   LastUnprocessedOSDMenuKey = 0;

tFontDataUC             OSDMenuFont_10;
tFontDataUC             OSDMenuFont_12;
tFontDataUC             OSDMenuFont_14;
tFontDataUC             OSDMenuFont_16;
tFontDataUC             OSDMenuFont_18;
tFontDataUC             OSDMenuFont_20;
tFontDataUC             OSDMenuFont_20B;

void (*CallbackProcedure)(tOSDCB OSDCBType, word OSDRgn) = NULL;

void OSDMenuInitialize(bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, char *TitleLeft, char *TitleRight)
{
  TRACEENTER();

  tMenu                *pMenu;

  //Clear everything
  pMenu = &Menu[CurrentMenuLevel];

  memset(pMenu, 0, sizeof(tMenu));

  if(OSDRgn) TAP_Osd_Delete(OSDRgn);
  OSDRgn = 0;
  MyOSDRgn = 0;

  OSDMenuLoadStdFonts();

  pMenu->OSDMenuDisplayMode = OMDM_Standard;
  pMenu->AllowScrollingOfLongText = AllowScrollingOfLongText;
  pMenu->HasValueColumn = HasValueColumn;
  pMenu->NumberedItems = NumberedItems;
  pMenu->ScrollLoop = ScrollLoop;
  pMenu->ValueXPos = 350;
  pMenu->ValueXOffset = 15;
  pMenu->hasValueArrows = FALSE;
  pMenu->MaxItems = 30;
  pMenu->Item = TAP_MemAlloc(pMenu->MaxItems * sizeof(tItem));
  memset(&pMenu->Item[0], 0, pMenu->MaxItems * sizeof(tItem));

  OSDMenuButtonsClear();
  OSDMenuSetLineHeight(LH_Normal);

  if(TitleLeft)
    strncpy(pMenu->TitleLeft, TitleLeft, STDSTRINGSIZE);
  else
    pMenu->TitleLeft[0] = '\0';
  pMenu->TitleLeft[STDSTRINGSIZE - 1] = '\0';

  if(TitleRight)
    strncpy(pMenu->TitleRight, TitleRight, STDSTRINGSIZE);
  else
    pMenu->TitleRight[0] = '\0';
  pMenu->TitleRight[STDSTRINGSIZE - 1] = '\0';

  MenuCursorType = CT_Standard;

  CallbackProcedure = NULL;

  TRACEEXIT();
}
