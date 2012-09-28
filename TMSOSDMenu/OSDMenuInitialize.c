#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

#include                "graphic/ScrollBarInvisible.gd"
#include                "graphic/ScrollBarVisible.gd"
#include                "graphic/ScrollBarKnob.gd"
#include                "graphic/InfoBox.gd"
#include                "graphic/MessageBoxSelectedButtonBackground.gd"

#include                "graphic/Button_0.gd"
#include                "graphic/Button_1.gd"
#include                "graphic/Button_2.gd"
#include                "graphic/Button_3.gd"
#include                "graphic/Button_4.gd"
#include                "graphic/Button_5.gd"
#include                "graphic/Button_6.gd"
#include                "graphic/Button_7.gd"
#include                "graphic/Button_8.gd"
#include                "graphic/Button_9.gd"
#include                "graphic/Button_ar.gd"
#include                "graphic/Button_audio.gd"
#include                "graphic/Button_aux.gd"
#include                "graphic/Button_blue.gd"
#include                "graphic/Button_cut.gd"
#include                "graphic/Button_down.gd"
#include                "graphic/Button_exit.gd"
#include                "graphic/Button_fav.gd"
#include                "graphic/Button_ffwd.gd"
#include                "graphic/Button_filelist.gd"
#include                "graphic/Button_green.gd"
#include                "graphic/Button_guide.gd"
#include                "graphic/Button_info.gd"
#include                "graphic/Button_jumpend.gd"
#include                "graphic/Button_jumpstart.gd"
#include                "graphic/Button_left.gd"
#include                "graphic/Button_list.gd"
#include                "graphic/Button_m.gd"
#include                "graphic/Button_menu.gd"
#include                "graphic/Button_mute.gd"
#include                "graphic/Button_nouse.gd"
#include                "graphic/Button_ok.gd"
#include                "graphic/Button_option.gd"
#include                "graphic/Button_pause.gd"
#include                "graphic/Button_play.gd"
#include                "graphic/Button_progminus.gd"
#include                "graphic/Button_progplus.gd"
#include                "graphic/Button_recall.gd"
#include                "graphic/Button_record.gd"
#include                "graphic/Button_red.gd"
#include                "graphic/Button_right.gd"
#include                "graphic/Button_rwd.gd"
#include                "graphic/Button_sat.gd"
#include                "graphic/Button_select.gd"
#include                "graphic/Button_sleep.gd"
#include                "graphic/Button_step.gd"
#include                "graphic/Button_stop.gd"
#include                "graphic/Button_subtitle.gd"
#include                "graphic/Button_ttx.gd"
#include                "graphic/Button_tv_radio.gd"
#include                "graphic/Button_up.gd"
#include                "graphic/Button_vf.gd"
#include                "graphic/Button_volminus.gd"
#include                "graphic/Button_volplus.gd"
#include                "graphic/Button_white.gd"
#include                "graphic/Button_yellow.gd"

#include                "graphic/ColorPicker.gd"
#include                "graphic/ColorPicker_CursorNone.gd"
#include                "graphic/ColorPicker_CursorDeselected.gd"
#include                "graphic/ColorPicker_ValueBackroundSelected.gd"

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

word                    ProgressBarOSDRgn = 0;
word                    ProgressBarFullRgn = 0;
dword                   ProgressBarLastValue = 0xfff;

word                    ColorPickerOSDRgn = 0;
dword                   ColorPickerColor;
dword                   ColorPickerDefaultColor;
tCurrentColorSelected   CurrentColorSelected;
int                     ColorPickerLastCursorRed, ColorPickerLastCursorGreen, ColorPickerLastCursorBlue;

dword                   ButtonColor;

void (*CallbackProcedure)(tOSDCB OSDCBType, word OSDRgn) = NULL;

void OSDMenuInitialize(bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, char *TitleLeft, char *TitleRight)
{
  tMenu                *pMenu;
  int                   i;

  //Clear everything
  pMenu = &Menu[CurrentMenuLevel];

  memset(pMenu, 0, sizeof(tMenu));
  for(i = 0; i < 4; i++)
    pMenu->ButtonXStart[i] = 55;

  if(OSDRgn) TAP_Osd_Delete(OSDRgn);
  OSDRgn = 0;
  MyOSDRgn = 0;

  pMenu->AllowScrollingOfLongText = AllowScrollingOfLongText;
  pMenu->HasValueColumn = HasValueColumn;
  pMenu->NumberedItems = NumberedItems;
  pMenu->ScrollLoop = ScrollLoop;
  pMenu->ValueXPos = 350;
  pMenu->hasValueArrows = FALSE;
  pMenu->Item = TAP_MemAlloc(30 * sizeof(tItem));

  pMenu->FontLeftTitle          = &Calibri_20_FontData;
  pMenu->FontRightTitle         = &Calibri_16_FontData;
  pMenu->FontListLineNumber     = &Calibri_14_FontData;
  pMenu->FontListNameColumn     = &Calibri_14_FontData;
  pMenu->FontListValueColumn    = &Calibri_14_FontData;
  pMenu->FontButtons            = &Calibri_12_FontData;
  pMenu->FontMemo               = &Calibri_14_FontData;

  pMenu->MaxItems = 30;
  memset(&pMenu->Item[0], 0, pMenu->MaxItems * sizeof(tItem));

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

  pMenu->OSDMenuDisplayMode = OMDM_Standard;
  ButtonColor = RGB(230, 230, 250);

  MenuCursorType = CT_Standard;

  CallbackProcedure = NULL;
}
